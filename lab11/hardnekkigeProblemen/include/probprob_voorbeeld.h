#pragma once

#include <vector>
#include "probprob.h"
using std::vector;
using std::pair;
using std::cout;
using std::endl;

/**
 * Voorbeeld implementatie van Probprob
 * Ze probeert een getal te vinden met een gegeven aantal cijfers dat zo klein mogelijk is.
 */
class Dom : public ProbProb<char>
{
public:
    Dom(int aantal) : aantal{aantal} {};

protected:
    virtual bool isOplossing(const vector<char> &deeloplossing);
    virtual double f(const vector<char> &oplossing);
    virtual vector<pair<char, double>> geefVolgendePunt(const vector<char> &deeloplossing);

    int aantal;
};