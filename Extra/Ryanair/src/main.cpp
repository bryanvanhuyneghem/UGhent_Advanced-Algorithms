#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "euler.h"
#include "graaf.hpp"

using std::string;

int main() {

	std::ifstream routes("ryanair.txt");
	string van, naar;
	while(routes >> van >> naar){
		std::cout << van << "->" << naar << "\n";
	}

	//PAS AAN EN VUL AAN
		
	return 0;
}

