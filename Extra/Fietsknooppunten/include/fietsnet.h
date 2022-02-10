#pragma once

#include <string>

#include "graaf.hpp"

/**
 * @brief Bevat alle velden beschikbaar in `knooppunten.csv`
 *
 */
struct Fietsknooppunt {
  int geoid;
  int knoopnr;
  std::string naam;
  double lat, lon;
};

std::ostream &operator<<(std::ostream &os, const Fietsknooppunt &k) {
  os << k.geoid << " (" << k.knoopnr << " - " << k.naam << ") @ [" << k.lat
     << "," << k.lon << "]";

  return os;
}

/**
 * @brief Een KnooppuntGraaf heeft knoopdata van het type 'Fietsknooppunt' en
 * takdata van het type `double` (=lengte van verbinding)
 */
typedef GraafMetKnoopEnTakdata<ONGERICHT, Fietsknooppunt, double>
    KnooppuntGraaf;

KnooppuntGraaf leesGraaf();

KnooppuntGraaf reduceerGraaf(const KnooppuntGraaf &orig);