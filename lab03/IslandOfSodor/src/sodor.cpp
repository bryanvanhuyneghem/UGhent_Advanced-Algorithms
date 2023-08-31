#include "sodor.h"
#include "graaf.h"
#include "stroomnet.h"
#include <algorithm>
#include <unordered_map>


int zoekMinimaleStationsluitingen(const std::vector<sodor::TrainStation> &stations,
                                  const std::string &startStationNaam, const std::string &eindStationNaam){

    //we duplicate each station in a start- and end-node.
    GraafMetTakdata<GERICHT, int> g(stations.size() * 2);

    //we connect the start- and end-node of each station with a link with capacity 1
    for (int i = 0; i < stations.size(); ++i)
    {
        g.voegVerbindingToe(i * 2, (i * 2) + 1, 1);
    }

    std::unordered_map<std::string, int> name_to_nr;
    for (int i = 0; i < stations.size(); ++i)
    {
        name_to_nr[stations[i].name] = i;
    }

    for (int i = 0; i < stations.size(); i++)
    {
        for (auto dest : stations[i].destinations)
        {
            g.voegVerbindingToe((i * 2) + 1, name_to_nr[dest.name] * 2, stations.size());
        }
    }

    int startNr = (name_to_nr[startStationNaam] * 2) + 1; //we use the end-node of Ffarquhar station to start our flow network from
    int eindNr = name_to_nr[eindStationNaam] * 2;         //we use the start-node of Tidmouth station to terminate our flow network in.

    Stroomnetwerk<int> sn{g, startNr, eindNr};
    return sn.geefStroom().geefCapaciteit();

}