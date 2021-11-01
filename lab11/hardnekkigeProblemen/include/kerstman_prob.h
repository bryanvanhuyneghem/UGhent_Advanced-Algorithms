#pragma once
#include "probprob.h"
#include <vector>
#include <iostream>


class kerstman_prob : public ProbProb<int>
{
public:
    kerstman_prob(vector<vector<double>> afstanden) : d(afstanden){};

    //void swapLokaal(vector<int> &s, int a, int b); //toegevoegd

    virtual double f(const vector<int> &s);
    virtual bool isOplossing(const vector<int> &deeloplossing);
    virtual vector<pair<int, double>> geefVolgendePunt(const vector<int> &deeloplossing);
    virtual void pickAtRandom(vector<int> &oplossing);
    virtual void verbeterLokaal(vector<int> &oplossing);

    // vector van afstanden tussen knopen
    // d[i][j] = afstand tussen i en j
    vector<vector<double>> d;
};