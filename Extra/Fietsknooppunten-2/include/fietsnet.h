#pragma once

#include <string>
#include "graaf.hpp"
#include <vector>

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

struct GraafZoekStap {
    int geoid; // geoid van de bezochte knoop
    int tak_nr; // tak waarmee deze knoop werd bereikt, -1 voor startknoop
    int diepte; // aantal stappen nodig om tot aan deze knoop te komen, 0 voor de startknoop
};

std::vector<GraafZoekStap> breedte_eerst_zoeken(const KnooppuntGraaf &g, int start_nr, int max_diepte);

