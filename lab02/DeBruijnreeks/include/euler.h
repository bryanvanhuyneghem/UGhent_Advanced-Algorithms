#ifndef __EULER_H
#define __EULER_H

#include "graaf.hpp"
#include <vector>

bool heeft_eulercircuit(const Graaf<ONGERICHT>& g);

bool heeft_eulercircuit(const Graaf<GERICHT>& g);

/**
 * Geeft een mogelijk Eulercircuit terug
 * 
 * @returns een geordende lijst met verbindingsnummers die
 *          een Eulercircuit vormen
 */ 
std::vector<int> eulercircuit(const Graaf<GERICHT>& g);

#endif //__EULER_H