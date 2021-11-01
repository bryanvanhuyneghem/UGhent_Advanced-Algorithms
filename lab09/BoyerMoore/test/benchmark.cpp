// #define CATCH_CONFIG_ENABLE_BENCHMARKING
// #include <catch2/catch.hpp>
// #include "boyermoore.h"
// #include <fstream>
// #include <sstream>
// using std::vector;
// using std::ifstream;
// using std::ios_base;
// using std::ostringstream;
// using std::runtime_error;


// string lees(string filename)
// {
// 	ifstream stream("files/" + filename, ios_base::in | ios_base::binary);
// 	if (!stream.is_open())
// 	{
// 		throw runtime_error("Could not open '" + filename + "'");
// 	}
// 	ostringstream sstream;
// 	sstream << stream.rdbuf();

// 	stream.close();

// 	return sstream.str();
// }

// vector<string> leesLijnen(string filename)
// {
// 	vector<string> lijnen;

// 	ifstream stream("files/" + filename, ios_base::in | ios_base::binary);
// 	if (!stream.is_open())
// 	{
// 		throw runtime_error("Could not open '" + filename + "'");
// 	}
// 	string lijn;
// 	while (std::getline(stream, lijn))
// 	{
// 		lijnen.push_back(lijn);
// 	}
// 	return lijnen;
// }

// TEST_CASE("Vergelijking performantie C++ string::find en BM-implementaties", "[benchmark]")
// {
// 	vector<string> naalden = leesLijnen("lingpatts");
// 	string hooiberg = lees("lingtext");

// 	BENCHMARK("C++ Find")
// 	{
// 		int totaal = 0; //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			int aantalNaaldenInHooiberg = 0;
// 			size_t pos = hooiberg.find(naald);
// 			while (pos != string::npos)
// 			{
// 				aantalNaaldenInHooiberg++;
// 				pos = hooiberg.find(naald, pos + 1);
// 			}
// 			totaal += aantalNaaldenInHooiberg;
// 		}
// 	};

// 	BENCHMARK("BM met heuristiek Verkeerde Karakter")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMVerkeerdeKarakter bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};

// 	BENCHMARK("BM-Horspool")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMHorspool bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};

// 	BENCHMARK("BM-Sunday")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMSunday bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};
// }

// TEST_CASE("Vergelijking performantie C++ string::find en BM-implementaties in DNA sequentie", "[benchmark]")
// {
// 	vector<string> naalden = leesLijnen("wgspatts");
// 	string hooiberg = lees("wgs_caam_env.seq");

// 	BENCHMARK("C++ Find")
// 	{
// 		int totaal = 0; //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			int aantalNaaldenInHooiberg = 0;
// 			size_t pos = hooiberg.find(naald);
// 			while (pos != string::npos)
// 			{
// 				aantalNaaldenInHooiberg++;
// 				pos = hooiberg.find(naald, pos + 1);
// 			}
// 			totaal += aantalNaaldenInHooiberg;
// 		}
// 	};

// 	BENCHMARK("BM met heuristiek Verkeerde Karakter")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMVerkeerdeKarakter bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};

// 	BENCHMARK("BM-Horspool")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMHorspool bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};

// 	BENCHMARK("BM-Sunday")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMSunday bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};
// }

// TEST_CASE("Vergelijking performantie C++ string::find en BM-implementaties met worst-case scenarios", "[benchmark]")
// {
// 	vector<string> naalden = leesLijnen("badpatt");
// 	string hooiberg = lees("bigbadtext");

// 	BENCHMARK("C++ Find")
// 	{
// 		int totaal = 0; //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			int aantalNaaldenInHooiberg = 0;
// 			size_t pos = hooiberg.find(naald);
// 			while (pos != string::npos)
// 			{
// 				aantalNaaldenInHooiberg++;
// 				pos = hooiberg.find(naald, pos + 1);
// 			}
// 			totaal += aantalNaaldenInHooiberg;
// 		}
// 	};

// 	BENCHMARK("BM met heuristiek Verkeerde Karakter")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMVerkeerdeKarakter bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};

// 	BENCHMARK("BM-Horspool")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMHorspool bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};

// 	BENCHMARK("BM-Sunday")
// 	{
// 		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
// 		for (const string &naald : naalden)
// 		{
// 			BMSunday bm(naald);

// 			auto plaatsen = bm.zoek(hooiberg);
// 			totaal += plaatsen.size();
// 		}
// 	};
// }