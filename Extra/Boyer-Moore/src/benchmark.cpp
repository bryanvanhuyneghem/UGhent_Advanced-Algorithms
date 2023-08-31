#include "boyermoore.h"
#include <fstream>
#include <sstream>
#include <iostream>
using std::vector;
using std::ifstream;
using std::ios_base;
using std::ostringstream;
using std::runtime_error;
using std::cout;

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

vector<string> leesLijnen(string filename)
{
	vector<string> lijnen;

	ifstream stream("files/" + filename, ios_base::in | ios_base::binary);
	if (!stream.is_open())
	{
		throw runtime_error("Could not open '" + filename + "'");
	}
	string lijn;
	while (std::getline(stream, lijn))
	{
		lijnen.push_back(lijn);
	}
	return lijnen;
}

void lingpatts_test() {
	
	vector<string> naalden = leesLijnen("lingpatts");
	string hooiberg = lees("lingtext");

	{
		int totaal = 0;  
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMVerkeerdeKarakter bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}

		cout << "Heuristiek van het verkeerde karakter vond " << totaal << " naalden met \t" << totaalAantalVergelijkingen << " vergelijkingen\n";
		
	}

	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMHorspool bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}
		cout << "Variant van Horspool vond " << totaal << " naalden met \t\t\t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	}

	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMSunday bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}
		cout << "Variant van Sunday vond " << totaal << " naalden met \t\t\t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	}
}

void dna_tests()
{
	vector<string> naalden = leesLijnen("wgspatts");
	string hooiberg = lees("wgs_caam_env.seq");


	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMVerkeerdeKarakter bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}
		cout << "Heuristiek van het verkeerde karakter vond " << totaal << " naalden met \t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	};

	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMHorspool bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}
		cout << "Variant van Horspool vond " << totaal << " naalden met \t\t\t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	}

	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMSunday bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}
		cout << "Variant van Sunday vond " << totaal << " naalden met \t\t\t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	}
}

void worstcase_test()
{
	vector<string> naalden = leesLijnen("badpatt");
	string hooiberg = lees("bigbadtext");

	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMVerkeerdeKarakter bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}

		cout << "Heuristiek van het verkeerde karakter vond " << totaal << " naalden met \t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	}

	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMHorspool bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}

		cout << "Variant van Horspool vond " << totaal << " naalden met \t\t\t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	}

	{
		int totaal = 0;  //totaal bijhouden om wegoptimaliseren te vermijden
		int totaalAantalVergelijkingen = 0;
		for (const string &naald : naalden)
		{
			BMSunday bm(naald);

			auto plaatsen = bm.zoek(hooiberg);
			totaal += plaatsen.size();
			totaalAantalVergelijkingen += bm.laatsteAantalKaraktervergelijkingen;
		}

		cout << "Variant van Sunday vond " << totaal << " naalden met \t\t\t" << totaalAantalVergelijkingen << " vergelijkingen\n";
	}
}

int main(){
	lingpatts_test();
	dna_tests();
	//worstcase_test();

	return 0;
}