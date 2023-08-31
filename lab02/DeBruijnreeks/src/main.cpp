#include <iostream>
#include "debruijnreeks.h"

int main() {
	std::cout << "Geef de lengte van het alfabet: ";

	int lengte_alfabet;
	if(!(std::cin >> lengte_alfabet)){
		std::cerr << "Ongeldige input!\n";
		return -1;
	}
	

	std::cout << "Geef de orde: ";

	int orde;
	if(!(std::cin >> orde)){
		std::cerr << "Ongeldige input!\n";
		return -1;
	}
	

	std::cout << "Een De Bruijnreeks met een alfabet van " << lengte_alfabet 
		<< " letters en een orde van " << orde 
		<< " is: \"" << genereer_debruijnreeks(lengte_alfabet, orde) << "\"\n";
		
	return 0;
}

