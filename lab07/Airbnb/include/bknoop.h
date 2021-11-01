#ifndef __bknoop
#define __bknoop
#include "btree.h"
#include "schijf.h"
#include <tuple>
#include <cmath>

template <class Sleutel, class Data, unsigned int orde>
class BKnoop
{
    friend class BTree<Sleutel, Data, orde>;

public:
    BKnoop<Sleutel, Data, orde>() = default;
    BKnoop<Sleutel, Data, orde>(const BKnoop<Sleutel, Data, orde>&) = default;
    BKnoop<Sleutel, Data, orde>(const Sleutel& sl, const Data& d, bool is_blad = true){
        sleutels[0] = sl;
        data[0] = d;
        aantalSleutels = 1;
        isblad = is_blad;
    }

    BKnoop<Sleutel, Data, orde>(BKnoop<Sleutel, Data, orde>&&) = delete;
    
    BKnoop<Sleutel, Data, orde>& operator=(BKnoop<Sleutel, Data, orde>&&) = delete;
    //BKnoop<Sleutel, Data, orde>& operator=(const BKnoop<Sleutel, Data, orde>&) = delete;

    const BKnoop<Sleutel, Data, orde> &operator=(const BKnoop<Sleutel, Data, orde> &b)
    {
        aantalSleutels = b.aantalSleutels;
        isblad = b.isblad;
        for (unsigned int i = 0; i < aantalSleutels; i++)
        {
            sleutels[i] = b.sleutels[i];
            data[i] = b.data[i];
        }
        if (!isblad)
        {
            for (unsigned int i = 0; i <= aantalSleutels; i++)
            {
                index[i] = b.index[i];
            }
        }
        return *this;
    }

    // hulpfunctie voor spliceMidden & splits
    void moveTo(BKnoop<Sleutel, Data, orde>& high, size_t high_start ){
        high.isblad = this->isblad;
        
        for(size_t i = high_start ; i < orde; i++){
            high.sleutels[i-high_start] = std::move(sleutels[i]);
            high.data[i-high_start] = std::move(data[i]);
            high.index[i-high_start+1] = index[i+1]; 
        }
        aantalSleutels = high_start;
        high.aantalSleutels = orde - high_start;
    }

    // sleutel die naar ouder moet, zit wel in de knoop en is het midden
    void spliceMidden(BKnoop<Sleutel, Data, orde>& high, Sleutel& sl, Data& d, bool rechts){
        assert(aantalSleutels == orde);

        const size_t midden_index = orde/2 - 1 + rechts;

        moveTo(high, midden_index + 1); 

        // juiste sleutelwaarden aanpassen in beide knopen
        aantalSleutels = midden_index;
        high.aantalSleutels = orde - midden_index - 1; // -1 omdat je de sleutel eruit haalt

        
        sl = std::move(sleutels[midden_index]);
        d = std::move(data[midden_index]);

    }

    // knoop in 2 hakken; sleutel die naar ouder moet zit nog niet in deze knoop
    void splits(BKnoop<Sleutel, Data, orde>& high, size_t high_start, BlokIndex nieuw_kind){
        assert(aantalSleutels == orde);
        
        moveTo(high, high_start);

        high.index[0] = nieuw_kind;

        
    }


    // array om in de knoop de sleutels bij te houden en de Data die bij een sleutel hoort
    // en array van BlokIndex met wijzers naar de indexen ("wijzers") op de schijf voor de knopen die horen bij de sleutel
    // de arrays worden gesorteerd bijgehouden!
    std::array<Sleutel, orde> sleutels; 
    std::array<Data, orde> data;
    std::array<BlokIndex, orde+1> index;

    // aantalSleutels die momenteel in de knoop zitten en of het al dan niet een blad is
    unsigned int aantalSleutels = 0;
    bool isblad = true;

    // functie die een nieuwe sleutel aan een knoop zal toevoegen
    int voegsleuteltoe(Sleutel key, Data val, BlokIndex bi);
    void schrijf(std::ostream &os) const;
};


template <class Sleutel, class Data, unsigned int orde>
int BKnoop<Sleutel, Data, orde>::voegsleuteltoe(Sleutel key, Data val, BlokIndex bi)
{
    assert(aantalSleutels < orde);
    size_t i = 0;
    while(i < aantalSleutels && key > sleutels[i]){
        i++;
    }
    if(i == orde){
        // knoop vol
        // Hier mogen we nooit in komen
        std::cerr << "knoop is al vol "/*<< key << " " << val << " " << bi */<< "\n";
        std::abort();
    }
    // element bestaat al
    else if(key == sleutels[i]){
        data[i] = std::move(val);
        std::cerr << "Sleutel bestond al "/* << key << " " << val << " " << bi */<< "\n";
    }
    // element in knoop bestaat nog niet -> toevoegen
    else {
        for(size_t j = aantalSleutels;  j > i; j--){
            sleutels[j] = std::move(sleutels[j-1]);
            data[j] = std::move(data[j-1]);
            index[j+1] = index[j];
        }
        aantalSleutels++;
        sleutels[i] = std::move(key);
        data[i] = std::move(val);
        index[i+1] = bi;
    }
    return i;
          

}

template <class Sleutel, class Data, unsigned int orde>
void BKnoop<Sleutel, Data, orde>::schrijf(std::ostream &os) const
{

    os << " --- " << aantalSleutels << " sleutels\n";
    for (int i = 0; i < aantalSleutels; i++)
    {
        os << sleutels[i] << " (" << data[i] << ") ";
    }
    os << "\n";
    if (isblad)
    {
        os << "knoop is blad";
    }
    else
    {
        os << "wijzers naar:\n";
        for (int j = 0; j <= aantalSleutels; j++)
        {
            os << index[j] << " - ";
        }
    }
    os << "\n";
}

#endif