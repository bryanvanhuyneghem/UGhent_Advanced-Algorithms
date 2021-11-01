#include "sodor.h"
#include "graaf.h"
#include "stroomnet.h"
#include <map>
#include <set>
#include <queue>


// niet-recursieve versie van DEZ. Eventuele todo: recursieve versie
// maar wat is de stopconditie die dan detecteert dat dat de stations zijn die gesloten moeten worden?
void zoekStations(Stroomnetwerk<int>& sn, std::vector<std::set<int>>& stations_per_niveau){
    std::set<int> gezien;
    std::queue<std::pair<int, int>> todo;

    todo.push(std::make_pair( (*(sn[0].begin())).first, 0)); // voeg knoop 0 zijn eerste buur toe, op niveau 0

    int niveau = 0;
    int knoop;

    while(!todo.empty()){
        knoop = todo.front().first;
        niveau = todo.front().second;
        todo.pop();

        if(gezien.find(knoop) == gezien.end()){
            if(stations_per_niveau.size() == niveau){
                std::set<int> st;
                stations_per_niveau.push_back(st);
            }

            // voor elke buur in de knoop (burenlijst overlopen)
            for(auto& buur : sn[knoop]){
                todo.push(std::make_pair((*(sn[buur.first].begin())).first, niveau+1));
                stations_per_niveau[niveau].insert(buur.first);
            }

            gezien.insert(knoop);
        }
    }

    stations_per_niveau.pop_back();
    stations_per_niveau.pop_back();
}


int zoekMinimaleStationsluitingen(const std::vector<sodor::TrainStation> &stations,
                                  const std::string &startStationNaam, const std::string &eindStationNaam)
{
    // 1.
    // Construeer een graaf waarmee je bovenstaande opgave kan oplossen als een klassiek stroomnetwerk-probleem. 
    // Van welke eigenschap van stroomnetwerken kan je gebruik maken? --> Slide 12: graafknopen spliten in inlet en outlet en capaciteit bepalen
    GraafMetTakdata<GERICHT, int> graaf(stations.size() * 2);

    std::map<std::string, int> inlets; // inlets bijhouden voor elk station
    std::map<std::string, int> outlets; // outlets bijhouden voor elk station
    int knoopNummer = 0;
    for (int i = 0; i < stations.size(); i++)
    {
        // inlet
        inlets[stations[i].name] = knoopNummer;
        knoopNummer++;
        // outlet
        outlets[stations[i].name] = knoopNummer;
        graaf.voegVerbindingToe(inlets[stations[i].name] , outlets[stations[i].name], 1); // verbinding tussen inlet en outlet (INTERN)
        knoopNummer++;
    }
    // Voor elk station
    for(int i = 0; i < stations.size(); i++){
        // Voor alle buren
        for (int j = 0; j < stations[i].destinations.size(); j++)
        {
            graaf.voegVerbindingToe(outlets[stations[i].name], inlets[stations[i].destinations[j].name], stations.size()); // verbinding tussen outlet en inlet van een buur (destination)
        }
    }

    //maximale stroom = # takdisjuncte paden die ervoor zorgen dat eindstation niet bereikt kan worden vanuit startstation
    Stroomnetwerk<int> sn(graaf, outlets[startStationNaam], inlets[eindStationNaam]);
    Stroomnetwerk<int> oplossing = sn.geefStroom(); // residueel netwerk maken
    
    // 2.
    // Bonusopgave: geef een lijst terug met de namen van de stations die dienen gesloten te worden. Definieer hiervoor zelf de nodige extra functies.
    //
    std::vector<std::set<int>> stations_per_niveau;
    zoekStations(sn, stations_per_niveau);

    int niveau = 0;;
    int min = stations_per_niveau[0].size();
    // zoek de bottleneck
    for( int i = 1; i < stations_per_niveau.size(); i++ ) {
        if( stations_per_niveau[i].size() < min ) {
            min = stations_per_niveau[i].size();
            niveau = i;
        }
    }

    std::cout << "De gesloten stations zijn: ";
    for( int station : stations_per_niveau[niveau] ) {
        std::cout << station/2 << ", "; // /2 want ons stroomnetwerk bevat dubbel de knopen (inlets en outlets) en we zijn enkel geïnteresseerd in de inlets (even knopen)
    } 
    std::cout << std::endl;
    
    return oplossing.geefCapaciteit();
}