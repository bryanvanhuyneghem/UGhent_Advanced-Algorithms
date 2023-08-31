#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "euler.h"
#include "debruijnreeks.h"
#include <map>

TEST_CASE("Voorwaarden Eulercircuit ongericht")
{
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

	g.voegVerbindingToe(5, 0);
	REQUIRE(!heeft_eulercircuit(g));
}

Graaf<GERICHT> maak_test_graaf()
{
	Graaf<GERICHT> g{2};
	g.voegVerbindingToe(0, 0);
	g.voegVerbindingToe(0, 1);
	g.voegVerbindingToe(1, 0);
	g.voegVerbindingToe(1, 1);

	return g;
}

TEST_CASE("Voorwaarden Eulercircuit gericht")
{
	Graaf<GERICHT> g = maak_test_graaf();

	REQUIRE(heeft_eulercircuit(g));

	g.voegKnoopToe();
	g.voegVerbindingToe(1, 2);
	REQUIRE(!heeft_eulercircuit(g));
}

void is_geldig_eulercircuit(const Graaf<GERICHT> &g, const std::vector<int> circuit)
{
	REQUIRE(circuit.size() == g.aantalVerbindingen());

	std::vector<int> verbindingen_count(g.aantalVerbindingen());
	for (int verbinding_nr : circuit)
	{
		REQUIRE(verbinding_nr < g.aantalVerbindingen());

		verbindingen_count[verbinding_nr]++;
	}
	REQUIRE(*std::min_element(verbindingen_count.begin(), verbindingen_count.end()) == 1);
	REQUIRE(*std::max_element(verbindingen_count.begin(), verbindingen_count.end()) == 1);
}

TEST_CASE("Eulercircuit 1")
{
	Graaf<GERICHT> g = maak_test_graaf();

	std::vector<int> circuit = eulercircuit(g);

	is_geldig_eulercircuit(g, circuit);
}

TEST_CASE("Eulercircuit 2")
{
	Graaf<GERICHT> g{5};
	g.voegVerbindingToe(0, 1);
	g.voegVerbindingToe(1, 2);
	g.voegVerbindingToe(2, 0);
	g.voegVerbindingToe(0, 3);
	g.voegVerbindingToe(3, 4);
	g.voegVerbindingToe(4, 0);

	g.voegVerbindingToe(4, 2);
	g.voegVerbindingToe(2, 4);

	g.voegVerbindingToe(3, 3);

	std::vector<int> circuit = eulercircuit(g);

	is_geldig_eulercircuit(g, circuit);
}

void controleer_debruijnreeks(std::string dbr, int alfabet_lengte, int orde)
{
	// generate all permutations that we should find

	int permutations_count = (int)pow(alfabet_lengte, orde);
	std::map<std::string, int> occurences;
	for (int i = 0; i < permutations_count; i++)
	{

		std::string perm{""};
		int v = i;
		for (int j = 0; j < orde; ++j)
		{
			perm = (char)('a' + (v % alfabet_lengte)) + perm;
			v /= alfabet_lengte;
		}
		occurences[perm] = 0;
	}

	dbr += dbr.substr(0, orde - 1); // because we need to test it as a circular string

	for (int i = 0; i <= dbr.size() - orde; ++i)
	{
		std::string substr = dbr.substr(i, orde);
		if (occurences.find(substr) == occurences.end())
		{
			throw std::domain_error("Unexpected substring \"" + substr + "\"");
		}
		occurences[substr] += 1;
	}

	for (auto &[perm, count] : occurences)
	{
		if (count != 1)
		{
			throw std::invalid_argument("Expected to find \"" + perm + "\" once, but found it " + std::to_string(count) + " times");
		}
	}
}

TEST_CASE("Voorbeelden uit de README")
{
	REQUIRE_NOTHROW(controleer_debruijnreeks("aabb", 2, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks("abbbabaa", 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks("aacbbccab", 3, 2));
}

TEST_CASE("Permutaties van voorbeelden uit README")
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

TEST_CASE("Genereer eenvoudige debruijn-reeksen")
{
	REQUIRE_NOTHROW(controleer_debruijnreeks(genereer_debruijnreeks(2, 2), 2, 2));
	REQUIRE_NOTHROW(controleer_debruijnreeks(genereer_debruijnreeks(2, 3), 2, 3));
	REQUIRE_NOTHROW(controleer_debruijnreeks(genereer_debruijnreeks(3, 2), 3, 2));
}

TEST_CASE("Genereer meerdere debruijn-reeksen")
{
	constexpr int values_to_test[] = {3,4,5,6,7};

	for (int alfabet_lengte : values_to_test)
	{
		for (int orde : values_to_test)
		{

			REQUIRE_NOTHROW(controleer_debruijnreeks(
				genereer_debruijnreeks(alfabet_lengte, orde),
				alfabet_lengte, orde));
		}
	}
}