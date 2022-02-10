#ifndef __EULER_H
#define __EULER_H

#include "graaf.hpp"
#include <vector>

bool heeft_eulercircuit(const Graaf<ONGERICHT>& g);

bool heeft_eulercircuit(const Graaf<GERICHT>& g);


struct Hop
{
    int knoop_nr;
    int verbindings_nr;
};


/**
 * Geeft een mogelijk Eulercircuit terug
 * 
 * @returns een geordende lijst met "hops" die
 *          een Eulercircuit vormen
 */ 
std::vector<Hop> eulercircuit(const Graaf<GERICHT>& g);

#endif //__EULER_H