#include "network-reader.h"
#include "sodor.h"
#include "stroomnet.h"
#include <iostream>

int main() {
	auto network = readNetwork("sodor-trainnetwork.json");

	// for(auto station: network){
	// 	std::cout << station.name << " has " << station.destinations.size() << " neighbours\n";
	// }

	int aantal_sluitingen = zoekMinimaleStationsluitingen(network, "Ffarquhar", "Tidmouth");


	std::cout << "Er dienen " << aantal_sluitingen << " stations te worden gesloten." << std::endl;

}

