#include <fstream>
#include <set>
#include <sstream>
#include <string>

#include "csv.hpp"
#include "fietsnet.h"

KnooppuntGraaf leesGraaf() {
  KnooppuntGraaf g;
  csv::CSVReader knooppunten_in("knooppunten.csv");

  // deze map beeldt de 'geoid' van elk fietsknooppunt af op de graafknoopnummer
  // die wordt toegewezen bij het uitvoeren van `voegKnoopToe`
  std::map<int, int> knoopnrs;

  for (auto& row : knooppunten_in) {
    int graaf_knoopnr =
        g.voegKnoopToe({row["geoid"].get<int>(), row["knoopnr"].get<int>(),
                        row["naam"].get<std::string>(),
                        row["lat"].get<double>(), row["lon"].get<double>()});
    knoopnrs[row["geoid"].get<int>()] = graaf_knoopnr;
  }

  csv::CSVReader trajecten_in("trajecten.csv");
  for (auto& row : trajecten_in) {
    g.voegVerbindingToe(knoopnrs[row["begin_geoid"].get<int>()],
                        knoopnrs[row["end_geoid"].get<int>()],
                        row["lengte_m"].get<double>());
  }

  return g;
}

/**
 * @brief Diepte Eerst Zoeken implementatie voor zoeken van een cluster 
 * van knopen die hetzelfde fietsknooppuntnummer hebben.
 * 
 * @param g 
 * @param knoopnr 
 * @param cluster 
 * @param huidigeKnoopNr 
 */
void vindCluster_DEZ(const KnooppuntGraaf& g, int knoopnr,
                 std::set<int>& cluster, int huidigeKnoopNr) {
  if (g.geefKnoopdata(knoopnr)->knoopnr ==
      g.geefKnoopdata(huidigeKnoopNr)->knoopnr) {
    cluster.insert(huidigeKnoopNr);

    for (auto& [buurnr, verbindingsnr] : g[huidigeKnoopNr]) {
      if (cluster.find(buurnr) == cluster.end()) {
        vindCluster_DEZ(g, knoopnr, cluster, buurnr);
      }
    }
  } 
}

std::set<int> vindCluster(const KnooppuntGraaf& g, int knoopnr) {
  std::set<int> cluster;

  //DEZ starten vanaf de gevraagde knoop
  vindCluster_DEZ(g, knoopnr, cluster, knoopnr);

  return std::move(cluster);
}

KnooppuntGraaf reduceerGraaf(const KnooppuntGraaf& orig) {
  std::set<int> gezien;
  KnooppuntGraaf nieuw;

  std::map<int, int> knooppuntMap;

  for (int i = 0; i < orig.aantalKnopen(); ++i) {
    if (gezien.find(i) != gezien.end()) {
      continue;
    }

    std::set<int> knooppuntCluster = vindCluster(orig, i);

    int eersteKnoop = *knooppuntCluster.begin();

    int nieuweKnoopNr = nieuw.voegKnoopToe(*orig.geefKnoopdata(eersteKnoop));

    for (int knoopnr : knooppuntCluster) {
      knooppuntMap[knoopnr] = nieuweKnoopNr;
      gezien.insert(knoopnr);
    }
  }

  // pas als we voor elke knoop uit de originele graaf de overeenkomstige 
  // 'nieuwe' knoopnummer weten kunnen we de verbindingen toevoegen
  for (int i = 0; i < orig.aantalKnopen(); ++i) {
    for (auto& [buurnr, verbindingsnr] : orig[i]) {
      if (buurnr < i) continue;

      if (knooppuntMap[i] != knooppuntMap[buurnr]) {
        nieuw.voegVerbindingToe(knooppuntMap[i], knooppuntMap[buurnr],
                                *orig.geefTakdata(i, buurnr));
      }
    }
  }

  return nieuw;
}
