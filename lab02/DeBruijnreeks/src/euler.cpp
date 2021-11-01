#include "euler.h"
//#include "componenten.cpp"

bool heeft_eulercircuit(const Graaf<ONGERICHT>& g){
    // All nodes must have an even amount of edges.
    // We can therefore check if the size of every node g[i], i.e. the
    // list of neighbor nodes, of our graph is an even number.
    for(int i = 0; i < g.aantalKnopen(); i++){
        if(g[i].size() % 2 != 0){
            return false;
            break;
        }
    }
    
    return true;
}

bool heeft_eulercircuit(const Graaf<GERICHT>& g){
    // For every node, we track how many incoming and outgoing edges it has.
    std::vector<std::pair<int, int> > in_uit_graden(g.aantalKnopen(), {0,0});

    // Vraag aan de graaf voor elke knoop zijn Burenlijst op en overloop deze lijst.
    // Vervolgens kunnen we voor deze knoop een uitgraad opmeten alsook voor de buur een ingraad opmeten

    // Check the neighbor list for every node in the graph.
    for(int nodeIndex = 0; nodeIndex < g.aantalKnopen(); nodeIndex++){
        // The number of neighbors of a node is equal the amount of >outgoing< edges associated with this node
        in_uit_graden[nodeIndex].second = g[nodeIndex].size();

        // For every neighbor node (our iterator) of our original node, if there is a connection, we can
        // increment the incoming edge count for that neighbor node by 1.  
        for(auto it = g[nodeIndex].begin(); it != g[nodeIndex].end(); it++){
            in_uit_graden[it->first].first++;
        }
    }

    // Check if all nodes have the same number of incoming and outgoing edges.
    // == graph is pseudosymmetric.
    for(int i = 0; i < g.aantalKnopen(); i++){
        if(in_uit_graden[i].first != in_uit_graden[i].second){
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
std::vector<int> eulercircuit(const Graaf<GERICHT>& g){
    // If the graph does not have an euler circuit, then there is no point running this function.
    if(!heeft_eulercircuit(g)){
        throw std::domain_error("De opgegeven graaf bevat geen Eulercircuit");
    }

    // Empty graph
    if(g.aantalKnopen() == 0){
        return std::vector<int>();
    }

    // For every node, keep track of the number of edges that have to be dealt with.
    std::vector<int> edges_per_node(g.aantalKnopen(), 0);
    for(int i = 0; i < g.aantalKnopen(); i++){
        edges_per_node[i] = g[i].size();
    }

    // Keep track of all edges in our graph that have to be visited. Initially, none have been
    // visited.
    std::vector<bool> edges_visited(g.aantalVerbindingen(), false);

    std::stack<int> path;
    std::vector<int> circuit; // Keeps track of the nodes on the Euler circuit
    circuit.reserve(g.aantalKnopen());

    int i = 0;
    path.push(i); // Start with node 0 and push it on to the stack.
    // Execute this loop while there are nodes on the stack that have to be dealt with.
    while(!path.empty()){
        // First, deal with all the edges of the node we are currently exploring.
        if(edges_per_node[i] > 0){
            path.push(i); // put the node on the stack
            edges_per_node[i]--; // decrease the number of edges of node i that must be explored by 1

            // Find a neighbor that has not yet been visited in the neighbor list of the node i, i.e. edges_visited[neighbor.second] == false
            // There will always be one, because the if-test above showed that number of connections for the node was bigger than 0
            auto unvisited_neighbor = std::find_if(std::begin(g[i]), std::end(g[i]),  [&edges_visited](const std::pair<int, int> &neighbor){
                return edges_visited[neighbor.second] == false;
            });

            i = unvisited_neighbor->first; // next node (the neighbor) we will visit in the next iteration of the while-loop
            edges_visited[unvisited_neighbor->second] = true; // we have visited this edge to this neighbor, so set the edge to true
        }
        else {
            circuit.push_back(i); // add the node to the circuit
            i = path.top(); // set new node that must be explored (will be one of the neighbors)
            path.pop(); // pop this neighbor
        }
    }


    // Finalisation; turn the list of nodes into a list of edges
    std::vector<int> euler_circuit;
    for(int i = circuit.size()-1; i > 0; i--){
        euler_circuit.push_back(g.verbindingsnummer(circuit[i], circuit[i-1]));
    }

    return euler_circuit;
}