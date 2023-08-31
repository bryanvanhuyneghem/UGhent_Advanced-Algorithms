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
        for(auto &[neighbour_nr, edge_nr]: g[i]){
            incoming_count[neighbour_nr]++;
        }
    }


    for(int i = 0; i < g.aantalKnopen(); i++){
        if(g[i].size() != incoming_count[i]){
            return false;
        }
    }
 
    return true;
}


struct Buur
{
    int neighbour_nr;
    int edge_nr;
};


/**
 * Geeft een mogelijk Eulercircuit terug
 * 
 * @returns een geordende lijst met verbindingsnummers die
 *          een Eulercircuit vormen
 */ 
std::vector<int> eulercircuit(const Graaf<GERICHT>& g){
    if(!heeft_eulercircuit(g)){
        throw std::domain_error("De opgegeven graaf bevat geen Eulercircuit");
    }

   std::vector<bool> edge_was_visited(g.aantalVerbindingen(), false);
    int edges_visited = 0;

    std::list<Buur> path{Buur{0, -1}}; //we start at node 0, and add an invalid edge
    std::list<Buur>::iterator start_pos = path.begin();

    while (edges_visited < g.aantalVerbindingen())
    {
        int start_node_nr = start_pos->neighbour_nr;
        std::list<Buur>::iterator path_insert_pos{start_pos};
        path_insert_pos++; //new edges need to be inserted after the current path pos

        //check if we can find unvisited edges in the current node
        for (auto &[neighbour_nr, edge_nr] : g[start_node_nr])
        {
            if (!edge_was_visited[edge_nr])
            {
                // follow edges at-random until we arrive at current_node_nr again

                int curr_edge_nr = edge_nr;
                int curr_node_nr = neighbour_nr;

                while (curr_node_nr != start_node_nr)
                {
                    path.insert(path_insert_pos, Buur{curr_node_nr, curr_edge_nr});
                    edge_was_visited[curr_edge_nr] = true;
                    edges_visited++;

                    //find the next edge to follow
                    const std::map<int,int> &curr_node = g[curr_node_nr];
                    std::map<int,int>::const_iterator n = curr_node.begin();

                    int node_nr, edge_nr;
                    std::tie(node_nr, edge_nr) = *n;

                    while (n != curr_node.end() && edge_was_visited[edge_nr])
                    {
                        n++;
                        std::tie(node_nr, edge_nr) = *n;
                    }

                    assert(n != curr_node.end()); // we should always find an unused outgoing edge in a valid Euler-graph

                    curr_node_nr = node_nr;
                    curr_edge_nr = edge_nr;
                }

                //also add the last followed edge to the path
                path.insert(path_insert_pos, Buur{curr_node_nr, curr_edge_nr});
                edge_was_visited[curr_edge_nr] = true;
                edges_visited++;
            }
        }

        //we followed all the unused edges in this node. Move to the next node in the path
        start_pos++;
        assert(start_pos != path.end());
    }

    //convert our Buur-list to a vector of edges
    std::vector<int> path_of_edge_nrs(g.aantalVerbindingen());
    std::list<Buur>::const_iterator it = path.begin();
    it++; //skip invalid edge at the beginning of the path

    for (int i = 0; i < g.aantalVerbindingen(); ++i)
    {
        path_of_edge_nrs[i] = it->edge_nr;
        it++;
    }

    return path_of_edge_nrs;
}