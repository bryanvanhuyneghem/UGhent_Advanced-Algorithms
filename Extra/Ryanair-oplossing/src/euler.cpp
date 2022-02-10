#include "euler.h"
#include <list>
#include <map>

bool heeft_eulercircuit(const Graaf<ONGERICHT>& g){
    for(int i = 0; i< g.aantalKnopen(); i++){
        if(g[i].size() % 2 != 0){
            return false;
        }
    }
    return true;
}

bool heeft_eulercircuit(const Graaf<GERICHT>& g){
    std::vector<int> incoming_count(g.aantalKnopen(), 0);

    for(int i = 0; i < g.aantalKnopen(); i++){
        for(auto &[knoop_nr, verbindings_nr]: g[i]){
            incoming_count[knoop_nr]++;
        }
    }


    for(int i = 0; i < g.aantalKnopen(); i++){
        if(g[i].size() != incoming_count[i]){
            return false;
        }
    }
 
    return true;
}


/**
 * Geeft een mogelijk Eulercircuit terug
 * 
 * @returns een geordende lijst met verbindingsnummers die
 *          een Eulercircuit vormen
 */ 
std::vector<Hop> eulercircuit(const Graaf<GERICHT>& g){
    if(!heeft_eulercircuit(g)){
        throw std::domain_error("De opgegeven graaf bevat geen Eulercircuit");
    }

   std::vector<bool> verbinding_is_bezocht(g.aantalVerbindingen(), false);
    int verbindingen_bezocht = 0;

    std::list<Hop> pad{Hop{0, -1}}; //we start at node 0, and add an invalid edge
    std::list<Hop>::iterator start_pos = pad.begin();

    while (verbindingen_bezocht < g.aantalVerbindingen())
    {
        int start_node_nr = start_pos->knoop_nr;
        std::list<Hop>::iterator pad_insert_pos{start_pos};
        pad_insert_pos++; //new edges need to be inserted after the current path pos

        //check if we can find unvisited edges in the current node
        for (auto &[knoop_nr, verbindings_nr] : g[start_node_nr])
        {
            if (!verbinding_is_bezocht[verbindings_nr])
            {
                // follow edges at-random until we arrive at current_node_nr again

                int huidig_verbindings_nr = verbindings_nr;
                int huidig_buur_nr = knoop_nr;

                while (huidig_buur_nr != start_node_nr)
                {
                    pad.insert(pad_insert_pos, Hop{huidig_buur_nr, huidig_verbindings_nr});
                    verbinding_is_bezocht[huidig_verbindings_nr] = true;
                    verbindingen_bezocht++;

                    //find the next edge to follow
                    const std::map<int,int> &huidige_knoop = g[huidig_buur_nr];
                    std::map<int,int>::const_iterator n = huidige_knoop.begin();

                    int knoop_nr, verbindings_nr;

                    std::tie(knoop_nr, verbindings_nr) = *n;

                    while (n != huidige_knoop.end() && verbinding_is_bezocht[verbindings_nr])
                    {
                        n++;
                        std::tie(knoop_nr, verbindings_nr) = *n;
                    }

                    assert(n != huidige_knoop.end()); // we moeten altijd een volgende verbinding kunnen vinden in een geldige Euler-graaf

                    huidig_buur_nr = knoop_nr;
                    huidig_verbindings_nr = verbindings_nr;
                }

                //also add the last followed edge to the path
                pad.insert(pad_insert_pos, Hop{huidig_buur_nr, huidig_verbindings_nr});
                verbinding_is_bezocht[huidig_verbindings_nr] = true;
                verbindingen_bezocht++;
            }
        }

        //we followed all the unused edges in this node. Move to the next node in the path
        start_pos++;
        assert(start_pos != pad.end());
    }

    //verwijder ongeldige start-hop
    pad.pop_front();

    return {pad.begin(), pad.end()};
}
