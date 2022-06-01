#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <vector>
#include <algorithm>
#include "graaf.hpp"
#include "componenten.cpp"
#include "woordspel.cpp"

using namespace std;

Graaf<GERICHT> maak_test_graaf()
{
	Graaf<GERICHT> g{15};
	g.voegVerbindingToe(0, 1);
	g.voegVerbindingToe(1, 2);
	g.voegVerbindingToe(2, 3);
	g.voegVerbindingToe(3, 0);
	g.voegVerbindingToe(3, 9);

	g.voegVerbindingToe(4, 5);
	g.voegVerbindingToe(5, 4);

	g.voegVerbindingToe(6, 7);
	g.voegVerbindingToe(7, 8);
	g.voegVerbindingToe(8, 6);
	g.voegVerbindingToe(8, 9);

	g.voegVerbindingToe(9, 10);

	g.voegVerbindingToe(10, 11);

	g.voegVerbindingToe(11, 12);
	g.voegVerbindingToe(12, 13);
	g.voegVerbindingToe(13, 14);
	g.voegVerbindingToe(14, 11);
	g.voegVerbindingToe(14, 12);
	g.voegVerbindingToe(13, 12);

	return g;
}

TEST_CASE("Preorder Test", "[DFS]")
{
	vector<int> pre_order;
	diepte_eerst_zoeken(
		maak_test_graaf(), [&pre_order](int knoop_nr) { pre_order.push_back(knoop_nr); }, [](int knoop_nr) {});

	vector<int> correcte_volgorde = {0, 1, 2, 3, 9, 10, 11, 12, 13, 14, 4, 5, 6, 7, 8};
	REQUIRE(pre_order == correcte_volgorde);
}

TEST_CASE("Postorder Test", "[DFS]")
{
	vector<int> post_order;
	diepte_eerst_zoeken(
		maak_test_graaf(), [](int knoop_nr) {}, [&post_order](int knoop_nr) { post_order.push_back(knoop_nr); });

	vector<int> correcte_volgorde = {14, 13, 12, 11, 10, 9, 3, 2, 1, 0, 5, 4, 8, 7, 6};
	REQUIRE(post_order == correcte_volgorde);
}

TEST_CASE("Componentennummers", "[SCC]")
{
	vector<int> component_nummers =
		sterk_geconnecteerde_componenten(maak_test_graaf());

	vector<int> correcte_component_nrs = {5, 5, 5, 5, 4, 4, 3, 3, 3, 2, 1, 0, 0, 0, 0};

	REQUIRE(component_nummers == correcte_component_nrs);
}

TEST_CASE("Componentengraaf", "[SCC]")
{
	Graaf<GERICHT> g = maak_test_graaf();

	vector<int> component_nummers = sterk_geconnecteerde_componenten(g);
	Graaf<GERICHT> cg = componenten_graaf(g, component_nummers);  
	CHECK(cg.aantalVerbindingen() == 4); 
	CHECK(cg.verbindingsnummer(5, 2) >= 0); 
	CHECK(cg.verbindingsnummer(3, 2) >= 0); 
	CHECK(cg.verbindingsnummer(2, 1) >= 0); 
	CHECK(cg.verbindingsnummer(1, 0) >= 0); 
}


TEST_CASE("Eerste kring ketting", "[Woordketen]")
{
	auto g = leesGraaf("/home/bryan/UGhent_Advanced-Algorithms/lab01/Kettingwoorden/woordenlijst.txt", "/home/bryan/UGhent_Advanced-Algorithms/lab01/Kettingwoorden/takkenlijst.txt");
	
	CHECK(g.aantalVerbindingen() == 225825); 

	auto componenten = sterk_geconnecteerde_componenten(g);

	int grootste_component_nr = grootste_component_nummer(componenten);

	std::ostringstream stream;
	stream << eersteKringKetting(g, componenten, grootste_component_nr);
	std::string str = stream.str();

	CHECK(str.size() == 10200); 
	CHECK(str.substr(0,19) == "aagtappelaardstraal"); 
	CHECK(str.substr(4999,29) == "grammofoonplaatstejaarsalaris"); 
}

TEST_CASE("Test: grootste_component_nummer", "[Eigen test]"){
	auto g = maak_test_graaf();
	auto componenten = sterk_geconnecteerde_componenten(g);
	int grootste_component_nr = grootste_component_nummer(componenten);
	CHECK(grootste_component_nr == 5);
}