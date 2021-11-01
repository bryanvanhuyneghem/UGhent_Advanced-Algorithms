#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "boyermoore.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using std::string;
using std::vector;

struct TekstZoekTest
{
	string naald;
	string hooiberg;

	int aantal;
	int aantalVergelijkingenHeuristiekVerkeerdeKarakter;
	int aantalVergelijkingenHorspool;
	int aantalVergelijkingenSunday;
};

const TekstZoekTest tztests[] = {
	{"abra", "abracadabra", 2, 10, 9, 9},
	{"a", "abcabcabcabcdaabcdef", 6, 20, 20, 12},
	{"aabaac", "aabaacaacaabaabaac", 2, 22, 14, 20},
	{"aabaac", "aabaacdacaabaabaac", 2, 16, 14, 15},
	{"aaa", "aaaaaaaaaaaaaaaaaaaa", 18, 54, 54, 54}, //ouch!
	{"anaxanax", "anaxananaxanax", 1, 16, 14, 15},
	{"aaaaaaab", "aaaaaaxaaaaaay", 0, 7, 7, 4},
};

TEST_CASE("BM met heuristiek van verkeerde karakter", "[simpel]")
{

	for (auto tzt : tztests)
	{
		BMVerkeerdeKarakter bmvk(tzt.naald);

		auto plaatsen = bmvk.zoek(tzt.hooiberg);

		CHECK(plaatsen.size() == tzt.aantal);
		CHECK(bmvk.laatsteAantalKaraktervergelijkingen == tzt.aantalVergelijkingenHeuristiekVerkeerdeKarakter);

    }
	
}

TEST_CASE("BM-Horspool", "[simpel]")
{

	for (const auto &tzt : tztests)
	{
		BMHorspool bmh(tzt.naald);

		auto plaatsen = bmh.zoek(tzt.hooiberg);

		CHECK(plaatsen.size() == tzt.aantal);
		CHECK(bmh.laatsteAantalKaraktervergelijkingen == tzt.aantalVergelijkingenHorspool);
	}
}

TEST_CASE("BM-Sunday", "[simpel]")
{
	for (const auto &tzt : tztests)
	{
		BMSunday bms(tzt.naald);

		auto plaatsen = bms.zoek(tzt.hooiberg);

		CHECK(plaatsen.size() == tzt.aantal);
		CHECK(bms.laatsteAantalKaraktervergelijkingen == tzt.aantalVergelijkingenSunday);
	}
}
