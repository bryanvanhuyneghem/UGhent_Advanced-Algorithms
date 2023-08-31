#include "fietsnet.h"
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <queue>

#include "csv.hpp"

KnooppuntGraafMetInfo leesGraaf()
{

    KnooppuntGraaf g{};
    std::map<int, int> geoid_naar_knoopnr;

    csv::CSVReader knooppunten_in("knooppunten.csv");
    for (auto &row : knooppunten_in)
    {
        int graaf_knoopnr = g.voegKnoopToe({row["geoid"].get<int>(),
                                            row["knoopnr"].get<int>(),
                                            row["naam"].get<std::string>(),
                                            row["lat"].get<double>(),
                                            row["lon"].get<double>()});
        geoid_naar_knoopnr[row["geoid"].get<int>()] = graaf_knoopnr;
    }

    csv::CSVReader trajecten_in("trajecten.csv");
    for (auto &row : trajecten_in)
    {
        g.voegVerbindingToe(geoid_naar_knoopnr.at(row["begin_geoid"].get<int>()),
                            geoid_naar_knoopnr.at(row["end_geoid"].get<int>()),
                            row["lengte_m"].get<double>());
    }

    return {g, geoid_naar_knoopnr};
}

struct ZoekStap
{
    int knoop_nr;
    int verbinding_nr;
    int diepte;
};

std::vector<GraafZoekStap>
breedte_eerst_zoeken(const KnooppuntGraaf &g, int start_nr, int max_diepte)
{

    std::vector<GraafZoekStap> resultaat;

    std::queue<ZoekStap> te_onderzoeken;
    te_onderzoeken.push({start_nr, -1, 0});
    std::vector<bool> bezocht(g.aantalKnopen(), false);

    bool max_diepte_bereikt = false;
    while (!max_diepte_bereikt && !te_onderzoeken.empty())
    {
        ZoekStap huidige_stap = te_onderzoeken.front();
        te_onderzoeken.pop();

        if (!bezocht[huidige_stap.knoop_nr])
        {
            bezocht[huidige_stap.knoop_nr] = true;
            resultaat.push_back({g.geefKnoopdata(huidige_stap.knoop_nr)->geoid,
                                 huidige_stap.verbinding_nr,
                                 huidige_stap.diepte});

            // enkel zoekstappen toevoegen die minder dan max_diepte ver liggen
            if (huidige_stap.diepte < max_diepte)
            {
                for (auto &[buur_nr, verbinding_nr] : g[huidige_stap.knoop_nr])
                {
                    te_onderzoeken.push({buur_nr, verbinding_nr, huidige_stap.diepte + 1});
                }
            }
        }
        else
        {
            // reeds gesettled, niets te doen
        }
    }

    return resultaat;
}
