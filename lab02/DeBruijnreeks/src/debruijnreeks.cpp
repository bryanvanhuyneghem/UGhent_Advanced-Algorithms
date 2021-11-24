#include <string>
#include "graaf.hpp"
#include "euler.h"
#include <cmath>


// length of alphabet = M
// order = N
// M^N
std::string genereer_debruijnreeks(int alfabet_lengte, int orde){
    // Create a graph with alphabet_lengte^(orde-1) nodes and edges between nodes as "state transitions".
    int nodeCount = std::pow(alfabet_lengte, orde-1);
    GraafMetTakdata<GERICHT, int> g(nodeCount);

    // Add the edges to the graph
    std::map<int, int> takdata_mapping; // mapping to easily get the edge data for an edge; this is a trade-off in space; complexity O(E)
    for(int knoop_nr = 0; knoop_nr < nodeCount; knoop_nr++){
        int shifted = (knoop_nr*alfabet_lengte) % nodeCount; // left shift the first number; on the right most position you will get a 0
        for(int i = 0; i < alfabet_lengte; i++){ // Loop over all possible letters in the alphabet
            int buur = shifted + i; // add value (i) of the edge with shifted -> the value will on the rightmost position (0) --> 0+i
            int verbindingsnummer = g.voegVerbindingToe(knoop_nr, buur, i);
            takdata_mapping[verbindingsnummer] = i; // leg mapping vast
        }
    }

    // Find the Euler circuit.
    std::vector<int> circuit = eulercircuit(g);

    // Construct the dbr as a string.
    std::stringstream ss;
    for(int element : circuit){
        ss << (char) (takdata_mapping[element] + 'a');
    }
    return ss.str();
}