#include "fietsnet.h"
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <list>
#include <queue>

#include "csv.hpp"

KnooppuntGraafMetInfo leesGraaf()
{
    KnooppuntGraaf g;
    csv::CSVReader knooppunten_in("knooppunten.csv");

    std::map<int, int> knoopnrs;

    for (auto &row : knooppunten_in)
    {
        int graaf_knoopnr = g.voegKnoopToe({row["geoid"].get<int>(),
                                            row["knoopnr"].get<int>(),
                                            row["naam"].get<std::string>(),
                                            row["lat"].get<double>(),
                                            row["lon"].get<double>()});
        knoopnrs[row["geoid"].get<int>()] = graaf_knoopnr;
    }

    csv::CSVReader trajecten_in("trajecten.csv");
    for (auto &row : trajecten_in)
    {
        g.voegVerbindingToe(knoopnrs[row["begin_geoid"].get<int>()],
                            knoopnrs[row["end_geoid"].get<int>()],
                            row["lengte_m"].get<double>());
    }

    return {g, knoopnrs};
}

// behalve gewicht voegen we ook extra meta-data toe over hoe we in deze knoop geraakt zijn
// Dit is nuttig om het pad te reconstrueren.
struct KnoopMetGewicht
{
    int knoopnr;    // huidige te onderzoeken knoop
    int voorganger; // vanuit welke knoop werd deze knoop bereikt?
    int taknr;      // via welke tak werd deze knoop bereikt?
    double gewicht; // totale gewicht van start tot aan deze knoop
};

std::list<KortstePadStap>
kortstePad(const KnooppuntGraaf &g, int start_nr, int eind_nr, std::vector<int> &permanente_knoopnrs)
{

    auto cmp = [](const KnoopMetGewicht &a, const KnoopMetGewicht &b)
    { return b.gewicht < a.gewicht; };
    std::priority_queue<KnoopMetGewicht, std::vector<KnoopMetGewicht>, decltype(cmp)> tijdelijk;

    tijdelijk.push({start_nr, -1, -1, 0});

    std::map<int, KnoopMetGewicht> permanent;

    while (!tijdelijk.empty() && !permanent.contains(eind_nr))
    {
        auto k = tijdelijk.top();
        tijdelijk.pop();

        if (!permanent.contains(k.knoopnr))
        {
            permanent[k.knoopnr] = k;

            for (const auto &[buur_nr, verbinding_nr] : g[k.knoopnr])
            {
                tijdelijk.push({buur_nr,
                                k.knoopnr,
                                verbinding_nr,
                                k.gewicht + *g.geefTakdata(k.knoopnr, buur_nr)});
            }
        }
    }

    if (tijdelijk.empty())
    {
        throw std::logic_error("Geen pad tussen start en eind-knoop");
    }

    std::list<KortstePadStap> resultaat;

    int knoop_nr = eind_nr;
    while (knoop_nr != -1)
    {
        auto k = permanent.at(knoop_nr);
        resultaat.push_front({k.knoopnr, k.taknr, k.gewicht});
        knoop_nr = k.voorganger;
    }

    permanente_knoopnrs.clear();
    for(const auto& [knoop_nr, k] : permanent){
        permanente_knoopnrs.push_back(knoop_nr);
    }

    return std::move(resultaat);
}

struct BiDirKnoopMetGewicht : KnoopMetGewicht
{
    bool voorwaarts;
};

std::list<KortstePadStap>
kortstePadBidirectioneel(const KnooppuntGraaf &g, int start_nr, int eind_nr, std::vector<int> &permanente_knoopnrs)
{

    auto cmp = [](const BiDirKnoopMetGewicht &a, const BiDirKnoopMetGewicht &b)
    { return b.gewicht < a.gewicht; };
    std::priority_queue<BiDirKnoopMetGewicht, std::vector<BiDirKnoopMetGewicht>, decltype(cmp)> tijdelijk;

    tijdelijk.push({start_nr, -1, -1, 0, true});
    tijdelijk.push({eind_nr, -1, -1, 0, false});

    std::map<int, BiDirKnoopMetGewicht> permanent_voorwaarts;
    std::map<int, BiDirKnoopMetGewicht> permanent_achterwaarts;

    bool kortste_pad_gevonden = false;
    while (!tijdelijk.empty() && !kortste_pad_gevonden)
    {
        auto k = tijdelijk.top();
        tijdelijk.pop();

        if (k.voorwaarts && !permanent_voorwaarts.contains(k.knoopnr))
        {
            permanent_voorwaarts[k.knoopnr] = k;
            kortste_pad_gevonden = permanent_achterwaarts.contains(k.knoopnr);
        }
        else if (!k.voorwaarts && !permanent_achterwaarts.contains(k.knoopnr))
        {
            permanent_achterwaarts[k.knoopnr] = k;
            kortste_pad_gevonden = permanent_voorwaarts.contains(k.knoopnr);
        }
        else
        {
            continue;
        }

        for (const auto &[buur_nr, verbinding_nr] : g[k.knoopnr])
        {
            tijdelijk.push({buur_nr, k.knoopnr, verbinding_nr, k.gewicht + *g.geefTakdata(k.knoopnr, buur_nr), k.voorwaarts});
        }
    }

    if (tijdelijk.empty())
    {
        throw std::logic_error("Geen pad tussen start en eind-knoop");
    }

    int laagste_kost = -1;
    int voorwaartse_knoop = -1, achterwaartse_knoop = -1, gem_tak_nr = -1;

    for (const auto &[a, kmk_a] : permanent_voorwaarts)
    {
        for (const auto &[b, kmk_b] : permanent_achterwaarts)
        {
            int gemeenschappelijke_tak_nr = g.verbindingsnummer(a, b);

            if (gemeenschappelijke_tak_nr != -1)
            {
                double totaal_gewicht = kmk_a.gewicht + *g.geefTakdata(a, b) + kmk_b.gewicht;
                if (laagste_kost == -1 || totaal_gewicht < laagste_kost)
                {
                    voorwaartse_knoop = a;
                    achterwaartse_knoop = b;
                    gem_tak_nr = gemeenschappelijke_tak_nr;
                    laagste_kost = totaal_gewicht;
                }
            }
        }
    }

    std::list<KortstePadStap> resultaat;

    int knoop_nr = voorwaartse_knoop;

    while (knoop_nr != -1)
    {
        auto k = permanent_voorwaarts.at(knoop_nr);
        resultaat.push_front({k.knoopnr, k.taknr, k.gewicht});
        knoop_nr = k.voorganger;
    }

    knoop_nr = achterwaartse_knoop;
    int verbindings_nr = gem_tak_nr;
    double gewicht = resultaat.back().totale_afstand + *g.geefTakdata(voorwaartse_knoop, achterwaartse_knoop);

    while (knoop_nr != -1)
    {
        auto k = permanent_achterwaarts.at(knoop_nr);
        resultaat.push_back({k.knoopnr, verbindings_nr, gewicht});
        verbindings_nr = k.taknr;
        if (k.taknr != -1)
        {
            gewicht += *g.geefTakdata(k.knoopnr, k.voorganger);
        }
        knoop_nr = k.voorganger;
    }


    permanente_knoopnrs.clear();
    for(const auto& [knoop_nr, k] : permanent_voorwaarts){
        permanente_knoopnrs.push_back(knoop_nr);
    }
    for(const auto& [knoop_nr, k] : permanent_achterwaarts){
        permanente_knoopnrs.push_back(knoop_nr);
    }

    return std::move(resultaat);
}
