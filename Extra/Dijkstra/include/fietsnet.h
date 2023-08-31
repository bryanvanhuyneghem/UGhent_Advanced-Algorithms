#pragma once

#include <string>
#include "graaf.hpp"
#include <list>

/**
 * @brief Bevat alle velden beschikbaar in `knooppunten.csv`
 *
 */
struct Fietsknooppunt
{
    int geoid;
    int knoopnr;
    std::string naam;
    double lat, lon;
};

std::ostream &operator<<(std::ostream &os, const Fietsknooppunt &k)
{
    os << k.geoid << " (" << k.knoopnr << " - " << k.naam << ") @ [" << k.lat << "," << k.lon << "]";

    return os;
}

/**
 * @brief Een KnooppuntGraaf heeft knoopdata van het type 'Fietsknooppunt' en
 * takdata van het type `double` (=lengte van verbinding)
 */
typedef GraafMetKnoopEnTakdata<ONGERICHT, Fietsknooppunt, double> KnooppuntGraaf;

struct KnooppuntGraafMetInfo
{
    KnooppuntGraaf graaf;
    std::map<int, int> geoid_naar_knoopnr; // afbeelding van geoids op knoopnrs in graaf
};

KnooppuntGraafMetInfo leesGraaf();

struct KortstePadStap {
    int knoopnr; 
    int tak_nr; // tak waarmee deze knoop werd bereikt, -1 voor startknoop
    double totale_afstand; //totale afstand in meters die werd afgelegd
};

bool operator==(const KortstePadStap& a, const KortstePadStap& b){
    return a.knoopnr == b.knoopnr && a.tak_nr == b.tak_nr && (a.totale_afstand - b.totale_afstand) < 0.01;
}

std::ostream &operator<<(std::ostream &os, const KortstePadStap &k)
{
    os << k.knoopnr << " via  " << k.tak_nr << " (afstand: " << k.totale_afstand << ")";

    return os;
}

std::list<KortstePadStap> kortstePad(const KnooppuntGraaf &g, int start_nr, int eind_nr, std::vector<int> &permanente_knoopnrs);


std::list<KortstePadStap> kortstePadBidirectioneel(const KnooppuntGraaf &g, int start_nr, int eind_nr, std::vector<int> &permanente_knoopnrs);
