#include "fietsnet.h"

#include <fstream>
#include <set>
#include <sstream>
#include <string>

#include "csv.hpp"

KnooppuntGraaf leesGraaf() {
  KnooppuntGraaf g;

  csv::CSVReader knooppunten_in("knooppunten.csv");

  for (auto &row : knooppunten_in) {
    std::cout << "Het bordje met geoid " << row["geoid"].get<int>() << " ("
              << row["knoopnr"].get<int>() << " van "
              << row["naam"].get<std::string>() << ") staat op locatie ["
              << row["lat"].get<double>() << ", " << row["lon"].get<double>()
              << "]\n";
  }

  csv::CSVReader trajecten_in("trajecten.csv");
  for (auto &row : trajecten_in) {
    std::cout << "De verbinding tussen " << row["begin_geoid"].get<int>()
              << " en " << row["end_geoid"].get<int>() << " is "
              << row["lengte_m"].get<double>() << "m lang\n";
  }

  return g;
}

KnooppuntGraaf reduceerGraaf(const KnooppuntGraaf &orig) {
  KnooppuntGraaf nieuw;

  return nieuw;
}
