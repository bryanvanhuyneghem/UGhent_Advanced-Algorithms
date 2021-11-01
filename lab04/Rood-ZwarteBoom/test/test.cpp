#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "rzwknoop.h"

/**
 * Representation Invariant test
 * 
 * Deze functie test of het gegeven RZWboom-object een geldige rood-zwart boom voorstelt.
 * 
 * Het test:
 * - Of de boom een geldige binaire boom is: zijn alle pointers geldig ingevuld?
 * - Of de sleutels in volgorde staan. 
 */
template <class Sleutel>
void repOKZoekboom(const RZWboom<Sleutel> & boom)
{
	Sleutel *vorige = 0; //houdt ref naar eerder gezien sleutel bij.
	if (boom.get()->ouder != 0)
		throw "wortel heeft geen null-ouder\n";
	boom.inorder([&vorige](const RZWknoop<Sleutel> &knoop) {
		//volgorde sleutels
		if (vorige && knoop.sleutel < *vorige)
		{
			throw "Verkeerde volgorde\n";
		};

		//ouderpointers
		for (const RZWknoop<Sleutel> *kind : {knoop.links.get(), knoop.rechts.get()})
			if (kind != 0 && kind->ouder != &knoop)
			{
				std::ostringstream fout;
				fout << "Ongeldige ouderpointer bij knoop " << kind->sleutel << "\n";
				fout << " wijst niet naar " << knoop.sleutel << "\n";
				throw fout.str();
			};
	});
}

RZWboom<int> maakEenvoudigeBoom()
{
	int points[5] = {4, 2, 5, 1, 3};
	RZWboom<int> boom = RZWboom<int>(std::make_unique<RZWknoop<int>>(points[0]));
	boom.get()->links = std::make_unique<RZWknoop<int>>(points[1]);
	boom.get()->rechts = std::make_unique<RZWknoop<int>>(points[2]);
	boom.get()->rechts->ouder = boom.get();
	boom.get()->links->ouder = boom.get();
	boom.get()->links->links = std::make_unique<RZWknoop<int>>(points[3]);
	boom.get()->links->rechts = std::make_unique<RZWknoop<int>>(points[4]);
	boom.get()->links->rechts->ouder = boom->links.get();
	boom.get()->links->links->ouder = boom->links.get();
	boom.zetKleur(zwart);
	boom.get()->links.zetKleur(zwart);
	boom.get()->rechts.zetKleur(zwart);
	return boom;
}


TEST_CASE("Roteer links", "[Eenvoudig]")
{
	RZWboom<int> boom = maakEenvoudigeBoom();
	bool naarLinks = true;
	boom.roteer(naarLinks);

	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 5);
	REQUIRE(boom.get()->links.geefKleur() == zwart);
	REQUIRE(boom.geefDiepte() == 4);
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

TEST_CASE("Roteer rechts", "[Eenvoudig]")
{
	RZWboom<int> boom = maakEenvoudigeBoom();
	bool naarLinks = false;
	boom.roteer(naarLinks);

	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 2);
	REQUIRE(boom.get()->links.geefKleur() == rood);
	REQUIRE(boom.get()->rechts.geefKleur() == zwart);
	REQUIRE(boom.geefDiepte() == 3);
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

TEST_CASE("Roteer 2 keer", "[Eenvoudig]")
{
	RZWboom<int> boom = maakEenvoudigeBoom();
	bool naarLinks = false;
	boom.roteer(naarLinks);
	naarLinks = true;
	boom.roteer(naarLinks);

	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 4);
	REQUIRE(boom.get()->links->sleutel == 2);
	REQUIRE(boom.get()->rechts.geefKleur() == zwart);
	REQUIRE(boom.geefDiepte() == 3);
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

TEST_CASE("Toevoegen aan boom", "[Eenvoudig]")
{
	RZWboom<int> boom = maakEenvoudigeBoom();
	boom.voegtoe(8);
	boom.voegtoe(7);
	boom.voegtoe(6);

	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 4);
	REQUIRE(boom.get()->links->sleutel == 2);
	REQUIRE(boom.get()->rechts.geefKleur() == rood);
	REQUIRE(boom.geefDiepte() == 4);
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

TEST_CASE("Construeren en toevoegen boom", "[Eenvoudig]")
{
	int points2[10] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10}; //,10,9,11,14,13,15};
	RZWboom<int> boom;
	//   std::cout << "punten toevoegen aan boom2: " << std::flush;
	for (int i : points2)
	{
		boom.voegtoe(i);
	}
	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 6);
	REQUIRE(boom.geefDiepte() == 4);
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

// test die geval van zwarte oom / niet op 1 lijn uitgebreid zal testen.
TEST_CASE("Toevoegen in boom 2", "[Eenvoudig]")
{
	int points[3] = {1,7,4}; 
	RZWboom<int> boom;
	for (int i : points)
	{
		boom.voegtoe(i);
	}
	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 4);
	REQUIRE(boom.geefDiepte() == 2);
	REQUIRE(boom.get()->rechts.geefKleur() == rood);
	REQUIRE(boom.get()->links.geefKleur() == rood);

    int points2[5] = {6,5,7,10,8};
	for (int i : points2)
	{
		boom.voegtoe(i);
	}
    boom.schrijf(std::cout);
	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 4);
	REQUIRE(boom.geefDiepte() == 4);
	REQUIRE(boom.get()->rechts->rechts.geefKleur() == zwart);
	REQUIRE(boom.get()->rechts->rechts->rechts.geefKleur() == rood);
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

TEST_CASE("Toevoegen oplopend", "[Eenvoudig]")
{
	RZWboom<int> boom;
	//   std::cout << "punten toevoegen aan boom2: " << std::flush;
	for (int i = 0; i < 100; i++)
	{
		boom.voegtoe(i);
	}
	REQUIRE(boom.geefKleur() == zwart);
	REQUIRE(boom.get()->sleutel == 31);
	REQUIRE(boom.geefDiepte() == 11);
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

TEST_CASE("Zoeken in boom", "[Eenvoudig]")
{
	int points2[15] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 9, 11, 14, 13, 15};
	RZWboom<int> boom;

	for (int i : points2)
	{
		boom.voegtoe(i);
	}

	REQUIRE(boom.zoekSleutel(10));
	REQUIRE(boom.zoekSleutel(5));
	REQUIRE_FALSE(boom.zoekSleutel(20));
	REQUIRE_NOTHROW(repOKZoekboom(boom));
}

TEST_CASE("Woordenboom", "[Toepassing]")
{
	RZWboom<string> woordenboom;
	string bestandsnaam = "../Ovidius", woord;
	std::ifstream file;
	file.open(bestandsnaam);
	int teller = 0, toegevoegd = 0;
	if (!file.is_open())
	{
		std::cout << "error opening file";
	}
	else
	{
		while (file >> woord)
		{
			if (!woordenboom.zoekSleutel(woord))
			{
				woordenboom.voegtoe(woord);
				toegevoegd++;
			}
			teller++;
		}
	}
	std::cout << "Je voegde " << toegevoegd << " unieke woorden toe aan de boom!\n";
	std::cout << woordenboom.get()->sleutel << std::endl;

    REQUIRE(woordenboom.geefDiepte() == 17);
	REQUIRE_NOTHROW(repOKZoekboom(woordenboom));
	
}