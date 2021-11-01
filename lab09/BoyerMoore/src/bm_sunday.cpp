#include "boyermoore.h"
#include <iostream>

BMSunday::BMSunday(const string &naald) : naald(naald)
{
    const int naald_lengte = naald.size();
    // Door de volledige tabel op -1 te initialiseren is die p-1-j altijd de juiste aantal verschuivingen:
    // ie. karakter bestaat niet in naald --> naald schuift p-1-(-1) = p == #karakters naald op
    for (int i = 0; i < ALFABET_GROOTTE; i++)
    {
        posities[i] = -1;
        //posities[i] = naald_lengte;
    }
    for (int j = 0; j < naald_lengte; j++)
    {
        // posities[character] = index meest rechtse
        //posities[naald[j]] = naald_lengte - 1 - j;
        posities[naald[j]] = j;
    }
}

std::queue<int> BMSunday::zoek(const string &hooiberg)
{
    laatsteAantalKaraktervergelijkingen = 0;
    std::queue<int> plaatsen_naald;
    if (hooiberg.size() < naald.size())
    {
        return plaatsen_naald;
    }

    const int naald_size = naald.size();
    const int hooiberg_size = hooiberg.size();
    int shift = 0;

    while (shift <= (hooiberg_size - naald_size))
    {
        int naald_idx = naald_size - 1;

        // karakters naald & hooiberg 1 per 1 vergelijken
        const auto comp = [this](char a, char b) {
            //laatsteAantalKaraktervergelijkingen++;
            return a == b;
        };
        while (naald_idx >= 0 && comp(hooiberg[shift + naald_idx], naald[naald_idx]))
        {
            naald_idx--;
        }

        // match
        if (naald_idx < 0)
        {
            // volledige match met naald; voeg toe aan queue en schuif naald met 1 positie op
            plaatsen_naald.push(shift);
            
        } 
        // mismatch
        const int net_voorbij = shift + naald_size; // shift + naald_size --> eentje VOORBIJ laatste karakter naald
        if(net_voorbij < hooiberg_size){ 
            // geen -1 hier
            shift += naald_size - posities[hooiberg[net_voorbij]];
        }
        // Moet eigenlijk niet, while loop zal falen
        else {
            break;
        }
        
        
    }

    return plaatsen_naald;
}
