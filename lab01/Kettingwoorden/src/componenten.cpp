/**
 * This file implements: 
 * 	-> the DFS algorithm
 * 	-> finding the strongly connected components in a given graph
 * 	-> the component graph of a given graph
*/

#include "graaf.hpp"
#include <vector>
#include <algorithm>

using namespace std;

/** Note:
 *  ----
 *  pre_order_func and post_order_func are both lambda functions that are called before and after a node has been processed,
 *  wtih the only argument being the node index.
 * 
*/

// Depth First Search
template <RichtType RT, typename PreOrderFunc, typename PostOrderFunc>
void diepte_eerst_zoeken(const Graaf<RT> &g, PreOrderFunc pre_order_func, PostOrderFunc post_order_func)
{
	// Keep track of which nodes have been visited
	vector<bool> visited(g.aantalKnopen(), false);

	for(int nodeIndex = 0; nodeIndex < visited.size(); nodeIndex++){
		// If the node has not yet been visited, explore it
		if(!visited[nodeIndex]){
			DFSRecursive(g, nodeIndex, visited, pre_order_func, post_order_func);
		}
	}
}

// DFS recursive helper function
template <RichtType RT, typename PreOrderFunc, typename PostOrderFunc>
void DFSRecursive(const Graaf<RT> &g, int nodeIndex, vector<bool> &visited, PreOrderFunc pre_order_func, PostOrderFunc post_order_func) {
	pre_order_func(nodeIndex);
	// Mark the current node as visited
	visited[nodeIndex] = true;

	
	auto it = g[nodeIndex].begin(); // note: 
									// it->first  : the node
									// it->second : the connection
	// Iterate over all child nodes
	while (it != g[nodeIndex].end()) {
		// Only consider nodes that have not yet been visited
		if (!visited[it->first]) {
			DFSRecursive(g, it->first, visited, pre_order_func, post_order_func);
		}
		it++;
	}

	post_order_func(nodeIndex);
}

// Finds the component each node belongs to use DFS
vector<int> sterk_geconnecteerde_componenten(const Graaf<GERICHT> &g)
{
	// Initialize a mapping for the nodes and their component number
	vector<int> result(g.aantalKnopen());

	// Step 1: create a reverse (transpose) graph 

    // traverse the adjacency list of given graph and 
    // for each edge (u, v) add an edge (v, u) in the 
    // reverse graph's adjacency list 

	Graaf<GERICHT> reversed(g.aantalKnopen());

	// Reverse the graph
    for (int i = 0; i < g.aantalKnopen(); i++) {   // vertex-loop
		for (auto it = g[i].begin(); it != g[i].end(); it++) { // edge-loop
			reversed.voegVerbindingToe(it->first,i);   // (from,to)
		}
	}
	
	// Step 2: DFS in the reversed graph to get the postorder of nodes
	stack<int> postorder;
	stack<int> preorder;

	diepte_eerst_zoeken(reversed,
						[&preorder] (int node) { preorder.push(node); },
						[&postorder] (int node) { postorder.push(node); }
	);

	vector<bool> visited = vector<bool>(g.aantalKnopen(), false);
	int componentNumber = 0;

	// Iterate over all postorder nodes
	while (!postorder.empty()) {
		int node = postorder.top();
		postorder.pop();
		if(!visited[node]) {
			// Use a lambda function to get all nodes for the current component
			DFSRecursive(
				g,
				node,
				visited,
				[](int node) { },
				[&result, componentNumber] (int node) {
					result[node] = componentNumber;
				}
			);
			componentNumber++;
		}

	}
	
	return result; // old: comp_nrs
}

// Returns the component graph of a given graph
Graaf<GERICHT> componenten_graaf(Graaf<GERICHT> g, std::vector<int> componentnummers)
{
	int numberOfComponents = (*max_element(componentnummers.begin(),componentnummers.end())) + 1; 
	//std::cout << "Aantal componenten: " << aantal_componenten << std::endl; 
	// Initialize a graph which will hold a node for each component and a connection between components if a connbection between nodes of
	// those components exists.	
	Graaf<GERICHT> componentGraph(numberOfComponents); // number of nodes of this component graph is equal to the number of components 

	// Explore neighbor nodes of every node in a component and check whether this neighbor in also in this component (i)
	// If not: the connection between these two nodes is a connection between two component graphs
	for (int i = 0; i < numberOfComponents; i++) { // <= ??
		// Explore the nodes of the graph
		for (int j = 0; j < g.aantalKnopen(); j++) {
			// Explore the node, if this node belongs to the component we are currently addressing
			if (componentnummers[j] == i) {
				auto it = g[j].begin();
				// Explore this node's neighbors
				while (it != g[j].end()) {
					// Check whether this neighbor node belongs to the same component
					if (componentnummers[it->first] != i) { // Note: componentnummers[it->first] : component number of neighbor node
						// A connection between nodes of two different components exists, so it is added
						// to the component graph as a connection between those two components.
						componentGraph.voegVerbindingToe(i, componentnummers[it->first]);
					}
					it++;
				}
			}
		}
	}
	
	return componentGraph;
}