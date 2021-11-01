#ifndef __SCHIJF
#define __SCHIJF
#include <map>
#include <iostream>
#include <cassert>
using BlokIndex = unsigned int;

//naamgeving gaat uit van de gebruiker: schrijf is een schrijfoperatie naar
//de schijf, enzovoorts
template <class Knoop>
class Schijf
{
private:

    std::map<BlokIndex, Knoop> store;
    //teller die het aantal toegevoegde elementen op de schijf zal tellen, merk op dat na verwijderen er ook "lege" indexen op de schijf zullen zijn.
    BlokIndex indexteller = 0;
public:
    //constructor
    Schijf() = default;
    // toegevoegd
    Schijf(Schijf&& s) = delete;
    Schijf(const Schijf& s) = delete;
    Schijf& operator=(Schijf&& s) = delete;
    Schijf& operator=(const Schijf& s) = delete;

    //schrijf: voegt een Knoop toe aan de schijf. Geeft de index terug van de nieuwe knoop (zodat die gebruikt kan worden in de BTree).
    BlokIndex schrijf(const Knoop &b)
    {
        ++indexteller;
        store[indexteller] = b;
        return indexteller;
    }

    // verwijder een blox index
    void verwijder(BlokIndex bi)
    {
        assert(bi != 0);
        store.erase(bi);
    }

    // nieuw woord op de schijf plaatsen
    void herschrijf(const Knoop &b, const BlokIndex bi)
    {
        assert(bi != 0);
        store[bi] = b;
    }

    // knoop van de schijf lezen en teruggeven
    Knoop lees(const BlokIndex bi)
    {
        assert(bi != 0);
        return store[bi];
    }
};

#endif
