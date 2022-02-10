#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "euler.h"

TEST_CASE("Voorwaarden Eulercircuit ongericht", "[euler]"){
	Graaf<ONGERICHT> g{6};
	g.voegVerbindingToe(0, 1);
	g.voegVerbindingToe(0, 3);
	g.voegVerbindingToe(1, 2);
	g.voegVerbindingToe(1, 4);
	g.voegVerbindingToe(1, 5);
	g.voegVerbindingToe(2, 3);
	g.voegVerbindingToe(2, 4);
	g.voegVerbindingToe(2, 5);
	g.voegVerbindingToe(3, 4);
	g.voegVerbindingToe(3, 5);

	
	REQUIRE(!heeft_eulercircuit(g));
	g.voegVerbindingToe(4, 5);

	REQUIRE(heeft_eulercircuit(g));

	g.voegVerbindingToe(5,0);
	REQUIRE(!heeft_eulercircuit(g));
}

Graaf<GERICHT> maak_test_graaf(){
	Graaf<GERICHT> g{2};
	g.voegVerbindingToe(0, 0);
	g.voegVerbindingToe(0, 1);
	g.voegVerbindingToe(1, 0);
	g.voegVerbindingToe(1, 1);

	return g;
}

TEST_CASE("Voorwaarden Eulercircuit gericht", "[euler]"){
	Graaf<GERICHT> g = maak_test_graaf();

	REQUIRE(heeft_eulercircuit(g));

	g.voegKnoopToe();
	g.voegVerbindingToe(1,2);
	REQUIRE(!heeft_eulercircuit(g));
}

void is_geldig_eulercircuit(const Graaf<GERICHT>& g, const std::vector<Hop> circuit){
	REQUIRE(circuit.size() == g.aantalVerbindingen());

	std::vector<int> verbindingen_count(g.aantalVerbindingen());
	for(auto & [knoop_nr, verbinding_nr]: circuit){
		REQUIRE(verbinding_nr < g.aantalVerbindingen());
		
		verbindingen_count[verbinding_nr]++;
	}
	REQUIRE(*std::min_element(verbindingen_count.begin(), verbindingen_count.end()) == 1);
	REQUIRE(*std::max_element(verbindingen_count.begin(), verbindingen_count.end()) == 1);

}

TEST_CASE("Eulercircuit 1", "[euler]"){
	Graaf<GERICHT> g = maak_test_graaf();

	std::vector<Hop> circuit = eulercircuit(g);

	is_geldig_eulercircuit(g, circuit);
}

TEST_CASE("Eulercircuit 2", "[euler]"){
	Graaf<GERICHT> g{5};
	g.voegVerbindingToe(0,1);
	g.voegVerbindingToe(1,2);
	g.voegVerbindingToe(2,0);
	g.voegVerbindingToe(0,3);
	g.voegVerbindingToe(3,4);
	g.voegVerbindingToe(4,0);

	g.voegVerbindingToe(4,2);
	g.voegVerbindingToe(2,4);
	
	g.voegVerbindingToe(3,3);

	std::vector<Hop> circuit = eulercircuit(g);

	is_geldig_eulercircuit(g, circuit);
}

