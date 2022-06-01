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
    
    // deze vector dient ENKEL voor de interne boekhouding, zodat bij het oproepen van
    // de destructor van Pboom automatisch alle Pknoop objecten ook worden verwijderd.
    // Negeer deze vector dus voor de implementatie van de zoek/voegtoe functie!
    std::vector<std::unique_ptr<Pknoop>> ptrs;
    Pknoop *maak_knoop(const StringMetBits &_sleutel, const int _data, int _index);
};


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
    // te implementeren
    return 0;
}

void Pboom::voegtoe(const StringMetBits &sleutel)
{
    //te implementeren
}

std::priority_queue<WordCount> Pboom::top20()
{
    
    std::priority_queue<WordCount> prio;
    // te implementeren
    return prio;
}

void Pboom::maak_eenvoudige_boom(){  
    // hard coded boom om zoek functie te kunnen evalueren
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

#endif
