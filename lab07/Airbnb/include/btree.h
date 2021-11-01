#ifndef __btree
#define __btree
#include "schijf.h"
#include <iostream>
#include <stack>
#include <memory>
#include <cmath>
using std::ostream;

using namespace std;

template <class Sleutel, class Data, unsigned int orde>
class BTree;
template <class Sleutel, class Data, unsigned int orde>
class BKnoop;

template <class Sleutel, class Data, unsigned int orde>
class BTree
{

    using Knoop = BKnoop<Sleutel, Data, orde>;

public:
    //constructor
    BTree(Schijf<Knoop> &s) : schijf(s)
    {
        Knoop wortel;
        wortelindex = schijf.schrijf(wortel);
    }

    // toevoegen, zoeken, data opvragen en data wijzigen:
    void voegtoe(const Sleutel& sleutel, const Data& waarde);     // waarde bij de sleutel wegschrijven op de schijf
    bool zoekSleutel(const Sleutel& sleutel);              // Kijken of sleutel aanwezig is op de schijf
    unique_ptr<Data> geefData(const Sleutel& sleutel);                // waarde bij de sleutel opvragen
    void updatedata(const Sleutel& sleutel, const  Data& waarde);  // waarde bij de sleutel aanpassen naar nieuwe waarde 

    // hulpfuncties en output functies
    Sleutel geefsleutelwortel(int index); // nodig voor testen // geeft de sleutel van de wortel terug op index.
    unsigned int aantalsleutelswortel();  // nodig voor testen // geeft het aantal sleutels in de wortelknoop terug

    //uitschrijven van boom
    void schrijfknoop(BlokIndex index, std::ostream &os);
    void schrijf(std::ostream &os);

private:

    // schijf waar de boom op staat en index van de wortel als attributen
    Schijf<Knoop> &schijf;
    BlokIndex wortelindex;

    // Zoekt een waarde in de sleutels van knoop die bij sleutel past.
    // Returned pointer van de waarde + het gevolgde pad zal in de stack zitten (nodig bij toevoegen).
    unique_ptr<Data> zoek(const Sleutel& sleutel, stack<BlokIndex> &pad);
};

template <class Sleutel, class Data, unsigned int orde>
void BTree<Sleutel, Data, orde>::voegtoe(const Sleutel & sleutel, const Data& waarde)
{
    std::stack<BlokIndex> pad;
    auto data_ptr = zoek(sleutel, pad);


    
    assert(data_ptr.get() == nullptr);
    // Ik heb hem gevonden, dus Sleutel bestaat al -> herschrijf
    /*if(data_ptr.get() != nullptr){
        BlokIndex bi = pad.top();
        Knoop k = schijf.lees(bi);
        k.voegsleuteltoe(sleutel, waarde, 0); 
        schijf.herschrijf(k, bi);
    }*/
    // niet gevonden, dus maak één aan
    
    BlokIndex nieuwKindindex = 0;
    Sleutel sl = sleutel;
    Data d = waarde;
    while(!pad.empty()){
        BlokIndex bi = pad.top();
        pad.pop();
        Knoop k = schijf.lees(bi);
        
        // er is nog plaats
        if(k.aantalSleutels < orde){
            k.voegsleuteltoe(sl, d, nieuwKindindex);
            schijf.herschrijf(k, bi);
            break;
        }
        // er is geen plaats meer
        else {
            // eerste optie: het midden van de orginele sleutels én de nieuwe sleutel -> nieuwe sleutel
            // 0 indexed
            constexpr int virtueel_midden = orde/2;
            int index = 0; // de zogezegde positie van sl indien hij in de reeks van k zou staan
            while(sl > k.sleutels[index] && index < k.aantalSleutels){
                index++;
            }

            Knoop high;
            
            if(index == virtueel_midden){
                // 1 6 11 16 21
                // 7?
                // i (zogezegde plaats van 7) = 3
                // als orde/2 ceil -> 3
                // dan 7 naar boven

                // sleutel moet in de ouder en moet alles hoger dan de sleutel naar nieuwkind
                k.splits(high, virtueel_midden, nieuwKindindex);
            }
            // anders moet sleutel binnen knoop naar boven
            else {
                Sleutel mid_sl;
                Data mid_data;
                
                k.spliceMidden(high, mid_sl, mid_data, index  > virtueel_midden );
            
                // indien de toe te voegen sleutel VOOR het midden ligt
                // 1 2 6 11 16 21
                // -> 6 (voeg toe aan de oude knoop)
                if(index < virtueel_midden) {
                    k.voegsleuteltoe(sl, d, nieuwKindindex);
                }
                // index > midden
                // 1 6 11 15 16 21
                // -> 11 (voeg toe aan de oude knoop)
                else {
                    high.voegsleuteltoe(sl, d, nieuwKindindex);
                }
                sl = std::move(mid_sl);
                d = std::move(mid_data);
            }
            
            nieuwKindindex = schijf.schrijf(high);
            schijf.herschrijf(k, bi);

            // root net gesplitst, dus we gaan een nieuwe root moeten aanmaken
            if(bi == wortelindex){
                assert(pad.empty());
                Knoop new_root(sl, d, false);
                new_root.index[0] = wortelindex; // = index van k
                new_root.index[1] = nieuwKindindex;

                wortelindex = schijf.schrijf(new_root);
            }
        }
    }
    
}

// public functie om sleutel in de BTree te gaan opzoeken
template <class Sleutel, class Data, unsigned int orde>
bool BTree<Sleutel, Data, orde>::zoekSleutel(const Sleutel & sleutel)
{
    std::stack<BlokIndex> st{};
    return zoek(sleutel, st).get() != nullptr;
}

// public functie om sleutel in de BTree te gaan
template <class Sleutel, class Data, unsigned int orde>
unique_ptr<Data> BTree<Sleutel, Data, orde>::geefData(const Sleutel & sleutel)
{
    std::stack<BlokIndex> st{};
    return zoek(sleutel, st);
}

// private zoek functie die ook het pad in de boom zal meegeven
template <class Sleutel, class Data, unsigned int orde>
unique_ptr<Data> BTree<Sleutel, Data, orde>::zoek(const Sleutel& sleutel, stack<BlokIndex> &path)
{
    BlokIndex huidigeIndex = wortelindex;
    
    while(true){
        Knoop huidigeKnoop = schijf.lees(huidigeIndex);
        path.push(huidigeIndex);
        size_t i = 0;
        while(i < huidigeKnoop.aantalSleutels && sleutel > huidigeKnoop.sleutels[i]){
            i++;
        }
    
        if(i != orde + 1  && sleutel == huidigeKnoop.sleutels[i]){
            return std::make_unique<Data>(Data(huidigeKnoop.data[i]));
        }
        else if(!huidigeKnoop.isblad){
            huidigeIndex = huidigeKnoop.index[i];
        }
        else {
            return std::unique_ptr<Data>(nullptr);
        } 
        
          
    }
}

/*
Hulpfuncties om gegevens van de wortel op te vragen bij de test cases
*/

template <class Sleutel, class Data, unsigned int orde>
Sleutel BTree<Sleutel, Data, orde>::geefsleutelwortel(int index)
{
    Knoop wortel = schijf.lees(wortelindex);
    return wortel.sleutels[index];
}

template <class Sleutel, class Data, unsigned int orde>
unsigned int BTree<Sleutel, Data, orde>::aantalsleutelswortel()
{
    Knoop wortel = schijf.lees(wortelindex);
    return wortel.aantalSleutels;
}

/*
Schrijf functies
*/
template <class Sleutel, class Data, unsigned int orde>
void BTree<Sleutel, Data, orde>::schrijfknoop(BlokIndex index, std::ostream &os)
{
    // knoop inlezen op de schijf
    Knoop knoop = schijf.lees(index);
    os << "index op schijf van knoop: " << index << "\n";
    // knoop uitschrijven
    knoop.schrijf(os);
}

template <class Sleutel, class Data, unsigned int orde>
void BTree<Sleutel, Data, orde>::schrijf(std::ostream &os)
{            
    // stack voor alle eventuele kinderknopen bij te houden en wortel er als eerste op plaatsen
    stack<BlokIndex> tebezoeken;
    tebezoeken.push(wortelindex);

    while (!tebezoeken.empty())
    {
        // knoop van de stack halen en uitschrijven
        BlokIndex huidige = tebezoeken.top();
        tebezoeken.pop();
        schrijfknoop(huidige, os);
        // om kinderen van deze knoop te kunnen vinden moet knoop ingelezen worden van de schijf,
        // is het geen blad worden de kinderen toegevoegd aan de stack
        Knoop knoop = schijf.lees(huidige);
        if (!knoop.isblad)
        {
            for (int j = 0; j <= knoop.aantalSleutels; j++)
            {
                tebezoeken.push(knoop.index[j]);
            }
        }
    }
}

#endif