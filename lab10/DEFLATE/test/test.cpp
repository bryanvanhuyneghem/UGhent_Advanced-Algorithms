#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER
#include <catch2/catch.hpp>
#include "lz77.h"
#include "suffix_array.h"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::ios_base;
using std::ostringstream;
using std::runtime_error;
using std::string;
using std::vector;

TEST_CASE("Juiste verwijzingen", "[suffixtabel]")
{
	SuffixArray sa("hottentottententententoonstellingen");

	CHECK(sa.zoekHerhaling(0, 0, 35).first == 0);
	CHECK(sa.zoekHerhaling(0, 1, 34).first == 0);						 //H
	CHECK(sa.zoekHerhaling(0, 2, 33).first == 0);						 //HO
	CHECK(sa.zoekHerhaling(0, 3, 32).first == 0);						 //HOT
	CHECK(sa.zoekHerhaling(0, 4, 31).first == 0);						 //HOTT
	CHECK(sa.zoekHerhaling(0, 5, 30).first == 0);						 //HOTTE
	CHECK(sa.zoekHerhaling(0, 6, 29).first == 0);						 //HOTTEN
	CHECK(sa.zoekHerhaling(0, 7, 28) == std::pair<int, int>({6, 6}));	 //HOTTENT (match op OTTENT)
	CHECK(sa.zoekHerhaling(0, 13, 22) == std::pair<int, int>({9, 3})); //HOTTENTOTTENT (match op ENTENT)
	CHECK(sa.zoekHerhaling(0, 19, 16) == std::pair<int,int>({4,15}));	 //HOTTENTOTTENTENTENT (match op ENTO, want search buffer groter dan in voorbeeld!)
	CHECK(sa.zoekHerhaling(0, 23, 12).first == 0);					 //HOTTENTOTTENTENTENTENTO
	CHECK(sa.zoekHerhaling(0, 24, 11).first == 0);					 //HOTTENTOTTENTENTENTENTOO
	CHECK(sa.zoekHerhaling(0, 25, 10).first == 0);					 //HOTTENTOTTENTENTENTENTOON
	CHECK(sa.zoekHerhaling(0, 26, 9).first == 0);						 //HOTTENTOTTENTENTENTENTOONS
	CHECK(sa.zoekHerhaling(0, 27, 8).first == 0);						 //HOTTENTOTTENTENTENTENTOONST
	CHECK(sa.zoekHerhaling(0, 28, 7).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTE
	CHECK(sa.zoekHerhaling(0, 29, 6).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTEL
	CHECK(sa.zoekHerhaling(0, 30, 5).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTELL
	CHECK(sa.zoekHerhaling(0, 31, 4).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTELLI
	CHECK(sa.zoekHerhaling(0, 32, 3).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTELLIN
	CHECK(sa.zoekHerhaling(0, 33, 2).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTELLING
	CHECK(sa.zoekHerhaling(0, 34, 1).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTELLINGE
	CHECK(sa.zoekHerhaling(0, 35, 0).first == 0);						 //HOTTENTOTTENTENTENTENTOONSTELLINGEN
}

TEST_CASE("Compress and decompress", "[lz77]")
{
	std::string voorbeeld = "hottentottententententoonstellingen";

	std::string compressed = compress_lz77(voorbeeld);
	std::string decompressed = decompress_lz77(compressed);

	REQUIRE(decompressed == voorbeeld);
	INFO("Compressed from  " << voorbeeld.size() << "bytes to " << compressed.size() << " bytes");
}

TEST_CASE("Compress a single character text", "[lz77]")
{
	std::string singlecharactertext(10000,'a');

	std::string compressed = compress_lz77(singlecharactertext);
	std::string decompressed = decompress_lz77(compressed);

	REQUIRE((100 * compressed.size()) / decompressed.size() < 2); // compress to less than 2% of original size
	if (decompressed != singlecharactertext)
	{
		INFO("Decompressed and original text do not match");
		REQUIRE(false);
	}
}


string lees(string filename)
{
	ifstream stream("files/" + filename, ios_base::in | ios_base::binary);
	if (!stream.is_open())
	{
		throw runtime_error("Could not open '" + filename + "'");
	}
	ostringstream sstream;
	sstream << stream.rdbuf();

	stream.close();

	return sstream.str();
}

TEST_CASE("Compress lingtext", "[lz77]")
{
	std::string lingtext = lees("lingtext");

	std::string compressed = compress_lz77(lingtext);
	std::string decompressed = decompress_lz77(compressed);

	REQUIRE((100 * compressed.size()) / decompressed.size() < 60); // compress to less than 60% of original size
	if (decompressed != lingtext)
	{
		INFO("Decompressed and original text do not match");
		REQUIRE(false);
	}
}

TEST_CASE("Compress wgs_caam_env", "[lz77]")
{
	std::string wgs_caam_env = lees("wgs_caam_env.seq");

	std::string compressed = compress_lz77(wgs_caam_env);
	std::string decompressed = decompress_lz77(compressed);

	REQUIRE((100 * compressed.size()) / decompressed.size() < 44); // compress to less than 44% of original size
	if (decompressed != wgs_caam_env)
	{
		INFO("Decompressed and original text do not match");
		REQUIRE(false);
	}
}
