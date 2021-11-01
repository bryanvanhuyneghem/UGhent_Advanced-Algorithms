#ifndef __PROBPROB_H
#define __PROBPROB_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <ctime>
using std::pair;
using std::vector;

/**
 * Probabilistic Probing
 *
 * De abstracte klasse ProbProb zoekt een vector van knopen die een optimale oplossing
 * biedt voor een gegeven probleem waarvoor de zoekruimte te groot is om ze
 * met backtracking helemaal af te gaan. Optimaal betekent met de beste waarde voor een
 * evaluatiefunctie f.
 * 
 * Hiervoor onderzoekt ze de zoekruimte op probabilistische wijze gebruikmakend van
 * een heuristiek h.
 * 
 * Een oplossing bestaat uit een reeks waarden W_0, W_1, ..., W_k (waarbij k niet
 * vooraf gegeven hoeft te zijn) die aan bepaalde voorwaarden voldoet en waarvoor f kan
 * berekend worden.
 * 
 * Oplossingen worden probabilistisch opgebouwd, Gegeven een deeloplossing W_0, ... W_j
 * wordt de verzameling V_j+1 van mogelijke waarden bepaald voor W_j+1. Tevens wordt de
 * heuristische waarde h(W_0, ... W_j, v) berekend voor alle v in V_j+1. het algoritme
 * kiest dan probabilistisch de volgende waarde W_j+1; de probabiliteit om v te kiezen
 * is evenredig met h(W_0, ... W_j, v).
 * 
 * Dit proces wordt n keren herhaald door de lidfunctie
 * 
 * vector<Waarde> ProbProb<Waarde>::geefOptimum(int n)
 * 
 * die de best gevonden oplossing teruggeeft.
 * 
 * Er wordt van uitgegaan dat een deeloplossing die een oplossing is nooit kan
 * uitgebreid worden tot een betere oplossing en dat een lege deeloplossing geen
 * oplossing kan zijn. bijgevolg mag de code nooit f evalueren op een lege
 * deeloplossing.
 */
template <class Waarde>
class ProbProb
{
public:
    /*
    * indien geefOptimum er niet in slaagt ook maar 1 oplossing te vinden geeft ze een
    * lege vector terug
    */
    vector<Waarde> geefOptimum(int n);

protected:
    /**
    * De functie geefProbOplossing probeert op probabilistische manier 1 oplossing te
    * vinden door constructief steeds verder te zoeken. Merk op: het kan zijn dat ze op
    * dood spoor belandt en een deeloplossing vindt die niet verder kan uitgebreid worden
    * maar ook geen oplossing is. In dat geval geeft ze een lege vector terug.
    */
    vector<Waarde> geefProbOplossing();

    /*****************************************************************************
    * De onderstaande functies moeten ingevuld worden voor specifieke problemen. *
    ******************************************************************************/

    virtual bool isOplossing(const vector<Waarde> &deeloplossing) = 0;
    virtual double f(const vector<Waarde> &oplossing) = 0;
    virtual vector<pair<Waarde, double>> geefVolgendePunt(const vector<Waarde> &deeloplossing) = 0;
};

template <class Waarde>
vector<Waarde> ProbProb<Waarde>::geefProbOplossing()
{
    srand(time(NULL));
    vector<Waarde> deeloplossing;
    vector<pair<Waarde, double>> mogelijkePunten;
    //oplossing construeren
    int k = 0;
    while (!isOplossing(deeloplossing))
    {
        k++;
        //volgende mogelijkheden en hun kansen berekenen
        mogelijkePunten = geefVolgendePunt(deeloplossing);
        // als er geen mogelijkheden meer zijn => lege oplossing teruggeven
        if (mogelijkePunten.size() == 0)
        {
            deeloplossing.reserve(deeloplossing.size());
            deeloplossing.clear();
            return deeloplossing;
        }
        //totale waarde kansen
        double totalekans = 0;
        for (auto &&[puntnummer, kans] : mogelijkePunten)
        {
            totalekans += kans;
        }
        // getal tussen 0 en total kans genereren
        double limiet = rand() * (totalekans / RAND_MAX);
        // kansen overlopen tot limiet bereikt is => aan oplossing
        Waarde punt;
        double teller = 0;
        for (auto &&[puntnummer, kans] : mogelijkePunten)
        {
            teller += kans;
            if (teller > limiet)
            {
                // ? deeloplossing.push_back(puntnummer);
                punt = puntnummer;
                break;
            }
        }
        // nieuw gevonden punt aan oplossing toevoegen
        deeloplossing.push_back(punt);
    };
    return deeloplossing;
};

template <class Waarde>
vector<Waarde> ProbProb<Waarde>::geefOptimum(int n)
{
    
    vector<Waarde> optimum;
    double score_optimum;

    for (int i = 0; i < n; i++)
    {
        vector<Waarde> poging = geefProbOplossing();
        if (poging.size() > 0)
        { //poging leverde geldige oplossing
            double score_poging = f(poging);

            // oplossing aanvaarden als er nog geen is of als poging beter is dan huidige oplossing
            if (optimum.size() == 0 || score_poging < score_optimum)
            {
                optimum = move(poging);
                score_optimum = score_poging;
            };
        };
    }
    return optimum;
};

#endif
