#ifndef __PATRICIA_H
#define __PATRICIA_H
#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <memory>


#include "patriciaknoop.h"
#include "stringmetbits.h"

using std::ostream;

struct WordCount : public std::pair<int, StringMetBits>
{
    WordCount(int count, StringMetBits w)
    {
        first = count;
        second = w;
    }
};

bool operator<(const WordCount &x, const WordCount &y)
{
    return y.first < x.first;
}


class Pboom
{
    friend class Pknoop;

public:
    Pboom(){ wortel=nullptr;}

    int zoek(const StringMetBits &sleutel);
    void voegtoe(const StringMetBits &sleutel);
    std::priority_queue<WordCount> top20(); 
    

    //hulpfuncties 
    void maak_eenvoudige_boom();        // hard gecodeerde voorbeeld boom
    void schrijf(ostream &os) const;    // schrijft de boom uit
    int aantalKnopen();                 // telt het aantal knopen
    StringMetBits geefWortelSleutel();  // vraagt de sleutel van de wortel op

private:
    Pknoop *wortel;
    Pknoop *zoek(Pknoop *k, const StringMetBits &sleutel, int index);
    Pknoop *voegtoe(Pknoop *k, Pknoop *parent, const StringMetBits &sleutel, int index);
    std::vector<std::unique_ptr<Pknoop>> ptrs;
    Pknoop *maak_knoop(const StringMetBits &_sleutel, const int _data, int _index);
};


Pknoop *Pboom::maak_knoop(const StringMetBits &_sleutel, const int _data, int _index) {
  std::unique_ptr<Pknoop> nieuw =  std::make_unique<Pknoop>(_sleutel, _data, _index);
  Pknoop *nieuw_ptr = nieuw.get();
  ptrs.push_back(std::move(nieuw));
  return nieuw_ptr;
}

int Pboom::aantalKnopen(){
    return ptrs.size();
}

StringMetBits Pboom::geefWortelSleutel(){
    return wortel->sleutel;
}

void Pboom::schrijf(ostream &os) const
{
    os << "Wortel van de boom: " << wortel->sleutel <<"\n";
    wortel->inorder([&os](const Pknoop &knoop){
        os << "(" << knoop.sleutel << " [" << knoop.data << "," << knoop.index << " ] )";
        os << "\n  Linkerkind: " <<  (knoop.links ? knoop.links->sleutel : "-----");
        os << "\n  Rechterkind: " <<  (knoop.rechts ? knoop.rechts->sleutel : "-----");
        os << "\n";
    });
}

int Pboom::zoek(const StringMetBits &sleutel)
{
    // We beginnen bij de wortel
    Pknoop *knoop = zoek(wortel, sleutel, -1);

    // Als de zoeksleutel niet in de boom zit, kan de zoek-methode toch een knoop tonen. Hier gebeurt de enige sleutel vergelijking.
    if ( !knoop || knoop->sleutel.compare(sleutel) != 0)
    {
        return 0;
    }

    // We hebben de correcte knoop gevonden..
    return knoop->data;
}

Pknoop *Pboom::zoek(Pknoop *k, const StringMetBits &sleutel, int index)
{
    // Als de index in de huidige knoop kleiner of gelijk aan de meegegeven index is
    // dan hebben we ofwel een terugverbinding naar een hoger gelegen knoop ofwel een
    // verbinding naar onszelf.
    // In beide situaties heeft verder zoeken geen zin meer.
    // We bubblen terug naar de zoek(sleutel) methode en doen daar een sleutel vergelijking.
    if (k->index <= index)
    {
        return k;
    }

    // We kunnen nog verder gaan.
    if (!sleutel.bit(k->index))
    {
        return zoek(k->links, sleutel, k->index);
    }
    else
    {
        return zoek(k->rechts, sleutel, k->index);
    }
}

void Pboom::voegtoe(const StringMetBits &sleutel)
{
    if (!this->wortel)
    {
        wortel = maak_knoop(sleutel, 1, sleutel.geefAantalBits());
        wortel->links = wortel;
        wortel->rechts = wortel;
        return;
    }

    // We zoeken naar de knoop met als sleutel, de zoeksleutel.
    Pknoop *knoop = zoek(wortel, sleutel, -1);

    // Situatie 1: sleutel bestaat.
    if (knoop->sleutel.compare(sleutel) == 0)
    {
        knoop->data++;
        return;
    }

    // Situatie 2: sleutel bestaat niet.
    // We zoeken de meest links verschillende bit.
    // Dan dalen we de boom opnieuw af:
    //  - als deze index groter (of gelijk) is voegen we hem tussen (tss 2 inwendige knopen)
    //  - als er een terugverbinding is, voegen we hem tussen. (dus blad)
    int bit = knoop->sleutel.verschilplaats(sleutel);

    Pknoop* nieuwe_knoop = voegtoe(wortel, nullptr, sleutel, bit);
    if(nieuwe_knoop->index < wortel-> index){
        wortel=nieuwe_knoop;
    }
}
 
Pknoop *Pboom::voegtoe(Pknoop *k, Pknoop *parent, const StringMetBits &sleutel, int index)
{
    // we krijgen een index die groter is dan de index van
    // knoop tussenvoegen || // toevoegen van een blad node
    if ((k->index >= index) || (parent && parent->index >= k->index))
    {
        bool bit_waarde = sleutel.bit(index);
        Pknoop* nieuw = maak_knoop(sleutel, 1, index);
        nieuw->links = (bit_waarde) ? k : nieuw;
        nieuw->rechts = (bit_waarde) ? nieuw : k;
        return nieuw;
    }
    //verder afdalen in de boom
    if (!sleutel.bit(k->index))
    { 
        k->links = voegtoe(k->links, k, sleutel, index);
    }
    else
    {
        k->rechts = voegtoe(k->rechts, k, sleutel, index);
    }
    return k;
}

std::priority_queue<WordCount> Pboom::top20()
{
    std::cout << "TOP 20" << std::endl;
    std::priority_queue<WordCount> prio;

    this->wortel->inorder([&prio](const Pknoop &knoop){
        WordCount p(knoop.data, knoop.sleutel);
        prio.push(p);
        if (prio.size() > 20)
        {
            prio.pop();
        }
    });
    return prio;
}


void Pboom::maak_eenvoudige_boom(){  
    wortel = maak_knoop(StringMetBits("jaja"),1,4);
    Pknoop* k1 = maak_knoop("alfa",2,32);
    Pknoop* k2 = maak_knoop("beta",3,6);
    Pknoop* k3 = maak_knoop("baby",2,13);
    Pknoop* k4 = maak_knoop("delta",1,5);

    wortel->links = k4;
    wortel->rechts = wortel;

    k1->links = k1;
    k1->rechts = k1;

    k2->links = k1;
    k2->rechts = k3;

    k3->links = k3;
    k3->rechts = k2;

    k4->links = k2;
    k4->rechts = k4;
}

#endif