#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "euler.h"
#include "debruijnreeks.h"
#include <map>

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

void is_geldig_eulercircuit(const Graaf<GERICHT>& g, const std::vector<int> circuit){
	REQUIRE(circuit.size() == g.aantalVerbindingen());

	std::vector<int> verbindingen_count(g.aantalVerbindingen());
	for(int verbinding_nr: circuit){
		REQUIRE(verbinding_nr < g.aantalVerbindingen());
		
		verbindingen_count[verbinding_nr]++;
	}
	REQUIRE(*std::min_element(verbindingen_count.begin(), verbindingen_count.end()) == 1);
	REQUIRE(*std::max_element(verbindingen_count.begin(), verbindingen_count.end()) == 1);

}

TEST_CASE("Eulercircuit 1", "[euler]"){
	Graaf<GERICHT> g = maak_test_graaf();

	std::vector<int> circuit = eulercircuit(g);

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

	std::vector<int> circuit = eulercircuit(g);

	is_geldig_eulercircuit(g, circuit);
}


void controleer_debruijnreeks(std::string dbr, int alfabet_lengte, int orde)
{
	// If the sequence is not of length M^N (M: length of alphabet, N: order), then it is not a valid sequence.
	if (dbr.length() != std::pow(alfabet_lengte, orde)) {
		throw std::invalid_argument{"Invalid DeBruijnreeks"}; 
	}

	// Keep track of all seen permutations
	std::map<std::string, bool> permutations;

	// Create a copy of the string and add the (order-1) chars to the end of it.
	// This is necessary to be able to check the existence of all permutations.
	// (Emulates that the string is a circuit)
	std::string copy(dbr);
	copy += dbr.substr(0, orde-1);
	
	// iterate over the length of the original string.
	for (int i = 0; i < dbr.length(); i++) {
		// The sequence is invalid if the letter is not in the given alphabet.
		if (alfabet_lengte < dbr[i] - 'a') {
			throw std::invalid_argument{"Invalid DeBruijnreeks"};
		}

		// Check if the permutation hasn't been seen yet.
		auto it = permutations.find(copy.substr(i, orde));
		if (it != permutations.end()) {
			// This permutation has already been seen!
			throw std::invalid_argument{"Invalid DeBruijnreeks"};
		}

		// Add the current, unseen permutation to the history
		permutations.insert(std::pair<std::string, bool>(dbr.substr(i, orde), true));
	}
	
	// The sequence is invalid if the number of seen permutations is bigger than M^N
	if (permutations.size() != std::pow(alfabet_lengte, orde)) {
		throw std::invalid_argument{"Invalid DeBruijnreeks"};
	}
}

TEST_CASE("Voorbeelden uit de README", "[controleer_debruijn]")
{
	REQUIRE_NOTHROW(controleer_debruijnreeks("aabb", 2, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("abbbabaa", 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks("aacbbccab", 3, 2));
}

TEST_CASE("Permutaties van voorbeelden uit README", "[controleer_debruijn]")
{

	REQUIRE_NOTHROW(controleer_debruijnreeks("abba", 2, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("bbaa", 2, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("baab", 2, 2));

	REQUIRE_NOTHROW(controleer_debruijnreeks("abbbabaa", 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks("bbbabaaa", 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks("bbabaaab", 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks("babaaabb", 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks("abaaabbb", 2, 3));

	REQUIRE_NOTHROW(controleer_debruijnreeks("aacbbccab", 3, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("acbbccaba", 3, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("cbbccabaa", 3, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("bbccabaac", 3, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("bccabaacb", 3, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("ccabaacbb", 3, 2));
}

TEST_CASE("Genereer eenvoudige debruijn-reeksen", "[debruijn]")
{
	REQUIRE_NOTHROW(controleer_debruijnreeks(genereer_debruijnreeks(2, 2), 2, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks(genereer_debruijnreeks(2, 3), 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks(genereer_debruijnreeks(3, 2), 3, 2));
}

TEST_CASE("Genereer meerdere debruijn-reeksen", "[debruijn]")
{
	for (int alfabet_lengte = 2; alfabet_lengte <= 26; ++alfabet_lengte)
	{
		for (int orde = 2; alfabet_lengte <= 10; ++alfabet_lengte)
		{
			DYNAMIC_SECTION("DeBruijnreeks {" << alfabet_lengte << "," << orde << "}")
			{
				REQUIRE_NOTHROW(controleer_debruijnreeks(
					genereer_debruijnreeks(alfabet_lengte, orde),
					alfabet_lengte, orde));
			}
		}
	}
}
