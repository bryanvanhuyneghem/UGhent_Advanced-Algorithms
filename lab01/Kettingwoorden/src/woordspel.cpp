#include "graaf.hpp"
#include "keten.hpp"
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <optional>
#include <map>
#include <string>

// Given
GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> leesGraaf(std::string woordenlijstFilename, std::string takkenlijstFilename)
{
    GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> woorden;
    std::unordered_map<std::string, int> woord_nr;

    std::ifstream in(woordenlijstFilename);
    std::string woord;
    while (in >> woord)
    {
        woord_nr[woord] = woorden.voegKnoopToe(woord);
    }

    std::cout << woord_nr.size() << " woorden ingelezen" << std::endl;

    in.close();
    in.clear();
    in.open(takkenlijstFilename);

    int genegeerd_count = 0;

    std::string van;
    std::string naar;
    while (in >> van >> naar >> woord)
    {
        int van_nr = woord_nr.at(van);
        int naar_nr = woord_nr.at(naar);

        if (woorden.verbindingsnummer(van_nr, naar_nr) == -1)
        {
            woorden.voegVerbindingToe(van_nr, naar_nr, woord);
        }
        else
        {
            genegeerd_count++;
        }
        // this is commented out to make the unit test execution result better readable
        //std::cout << std::endl;
    }

    return woorden;
}


// Find the component with the most nodes.
// components_nrs maps the node index (index of the vector) to the component it belongs to
int grootste_component_nummer(const std::vector<int> &component_nrs)
{
    int numberOfComponents = *std::max_element(component_nrs.begin(), component_nrs.end()) + 1; // returns the maximum element in range
    
    // Build a frequency table and keep track of the max value/index
    vector<int> freqTable(numberOfComponents, 0);
    int maxValue = -1; // the number of nodes associated with a component number
    int maxIndex = -1; // the component number

    
    for (int nodeNumber = 0; nodeNumber < component_nrs.size(); nodeNumber++) { 
        // Increment the frequency of the component number associated with the node number
        freqTable[component_nrs[nodeNumber]]++;
        if (freqTable[component_nrs[nodeNumber]] > maxValue) {
            maxValue = freqTable[component_nrs[nodeNumber]];
            maxIndex = component_nrs[nodeNumber];
        }
    }

    return maxIndex;
}

// Helper function to eersteKringKetting
bool findWordChainRecursive(const GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> &g,
                                int nodeIndex,
                                const vector<int> &component_nrs,
                                int component_nr,
                                std::map<int, bool> &visited,
                                int firstNodeIndex,
                                vector<string> &chain) {
    // Stop if the chain is back at the first word
    if (0 < chain.size() && firstNodeIndex == nodeIndex) {
        return true;
    }

    // Iterate over all child nodes, i.e. neighbors, of a current word
    auto child_it = g[nodeIndex].begin();
    while (child_it != g[nodeIndex].end()) {
        // Only child nodes with the correct component number and that haven't been visited yet are considered
        if (component_nrs[child_it->first] == component_nr &&
            visited.find(child_it->first) == visited.end()) {
                // Add the node to the visited map
                visited.insert(std::pair<int, bool>(child_it->first, true));
                // Add to the chain
                chain.push_back(*g.geefTakdata(nodeIndex, child_it->first));
                // Recursively build chain with current child node
                bool finished = findWordChainRecursive(g, child_it->first, component_nrs, component_nr, visited, firstNodeIndex, chain);
                if (finished) {
                    return true;
                }

                // If we get to this step in the program, a chain has not been detected.
                // We must remove the node from the chain vector and remove the node from the visited map
                chain.pop_back();
                visited.erase(visited.find(child_it->first));
        }
        // Move on to the next child (neighbor)
        child_it++;
    }

    // No more suitable child nodes, backtrack to the parent node
    return false; 
}

// Finds the first chain
Keten eersteKringKetting(const GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> &g,
                                        const std::vector<int> &component_nrs,
                                        int component_nr) {
    // Find the alphabetically first node
    int nodeIndex = -1;
    // woordenlijst.txt is alphabetically sorted, which means that the vector component_nrs will also be
    // 'alphabetically sorted'. Thus, the first occurence of the component_nr indicated the alphabetically first node.
    // Increment the nodeIndex as long as we have not found the first occurence of the desired component number in component_nrs
    while (nodeIndex++ < g.aantalKnopen()) {
        if (component_nrs[nodeIndex] == component_nr) {
            break;
        }
    }

    // Initialize a vector to keep track of the connections between nodes of the chain
    vector<string> chain;
    // A hashmap that keeps track of the visited nodes that are in the chain
    std::map<int, bool> visited;
    // Build the chain
    findWordChainRecursive(g, nodeIndex, component_nrs, component_nr, visited, nodeIndex, chain);

    return Keten{chain};
}



