#include "galadiner.h"

#include "graaf.hpp"
#include "stroomnet.h"

/**
 * @brief Zoekt een tafelverdeling voor de opgegeven delegaties en tafels
 *
 * @param delegaties Aantal afgevaardigden per delegatie
 * @param tafels Aantal plaatsen aan tafel
 * @return vector<vector<int>> Elke tafel wordt voorgesteld door een
 * `vector<int>` die de indexen bevat van de delegaties waarvan een
 * afgevaardigde kan plaatsnemen.
 *
 */
vector<vector<int>> zoek_tafelverdeling(vector<int> delegaties,
                                        vector<int> tafels) {
  const int begin_knoop = 0;
  const int eind_knoop = 1;
  const auto geef_delegatie_knoopnr = [](int idx) { return 2 + idx; };
  const auto geef_tafel_knoopnr = [&delegaties](int idx) {
    return 2 + delegaties.size() + idx;
  };

  GraafMetTakdata<GERICHT, int> g(2 + delegaties.size() + tafels.size());

  for (int i = 0; i < delegaties.size(); i++) {
    g.voegVerbindingToe(begin_knoop, geef_delegatie_knoopnr(i), delegaties[i]);

    for (int j = 0; j < tafels.size(); j++) {
      g.voegVerbindingToe(geef_delegatie_knoopnr(i), geef_tafel_knoopnr(j), 1);
    }
  }

  for (int j = 0; j < tafels.size(); j++) {
    g.voegVerbindingToe(geef_tafel_knoopnr(j), eind_knoop, tafels[j]);
  }

  Stroomnetwerk<int> opl_stroom =
      Stroomnetwerk<int>(g, begin_knoop, eind_knoop).geefStroom();

  vector<vector<int>> opl(tafels.size());

  for (int i = 0; i < delegaties.size(); i++) {
    for (int j = 0; j < tafels.size(); j++) {
      int* tak = opl_stroom.geefTakdata(geef_delegatie_knoopnr(i),
                                        geef_tafel_knoopnr(j));

      if (tak != nullptr && *tak == 1) {
        opl[j].push_back(i);
      }
    }
  }

  return opl;
}
