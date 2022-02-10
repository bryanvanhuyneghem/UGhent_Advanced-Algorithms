#include <list>
#include <queue>
#include <map>
#include <vector>
#include <cassert>

#include "graaf.hpp"

template<class Takdata>
struct KnoopMetKost {
  int knoop_nr;
  Takdata kost;
  int voorganger;

  KnoopMetKost(int knoop_nr, Takdata kost, int voorganger) : knoop_nr(knoop_nr), kost(kost), voorganger(voorganger){}

    /*
     * In deze functie gebruiken we een kleine "hack": een object met een kleinere kost wordt terugggegeven als groter.
     * De std::priority_queue geeft immers standaard het grootste element terug ipv het kleinste. 
     * 
     * Alternatief: std::less meegeven als 3e template parameter aan de pq
     */
  bool operator<(const KnoopMetKost& k) const {
    return kost > k.kost;
  }
};

template <RichtType RT, class Takdata>
std::list<int> shortest_path(const GraafMetTakdata<RT, Takdata>& g, int start_nr,
                             int eind_nr) {
  std::map<int, int> voorganger;

  std::priority_queue<KnoopMetKost<Takdata>, std::vector<KnoopMetKost<Takdata>>> pq; 

  pq.push(KnoopMetKost<Takdata>(start_nr, 0, -1));

  while (!pq.empty() && pq.top().knoop_nr != eind_nr) {
    auto kmk = pq.top();
    pq.pop();

    if(voorganger.find(kmk.knoop_nr) != voorganger.end()){
        // knoop werd reeds eerder gesettled: overslaan!
        continue;
    }

    voorganger[kmk.knoop_nr] = kmk.voorganger;
    //std::cout << "Settling " << kmk.knoop_nr << " met kost " << kmk.kost << " via " << kmk.voorganger << "\n";

    for (auto &[buur_nr, verbindings_nr] : g[kmk.knoop_nr]) {
      pq.push(KnoopMetKost<Takdata>(buur_nr,
                           kmk.kost + *g.geefTakdata(kmk.knoop_nr, buur_nr),
                           kmk.knoop_nr));
    }
  }

  if (pq.empty()) {
    return {};
  } else {
    assert(pq.top().knoop_nr == eind_nr);

    std::list<int> resultaat{eind_nr};

    int vg = pq.top().voorganger;
    while (vg != -1) {
      resultaat.push_front(vg);
      vg = voorganger[vg];
    }

    return resultaat;
  }
};
