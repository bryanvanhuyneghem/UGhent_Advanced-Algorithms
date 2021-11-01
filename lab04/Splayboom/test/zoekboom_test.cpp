#include <catch2/catch.hpp>
#include "zoekknoop.h"
#include "test_utils.h"
#include <algorithm>


//Test voor het toevoegen van knopen in een gewone zoekboom
TEST_CASE("Zoekboom toevoegen", "[eenvoudig]") {
    ZoekBoom<int, int> boom;
    int points[10] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10};
    for (int i:points) {
        boom.voegtoe(i, 2);
    }
    REQUIRE(boom.aantalKnopen() == 10);
    REQUIRE(boom->sleutel == 8);
    REQUIRE(boom.geefDiepte() == 4);
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}

//Test voor een gewone zoekboom evenwichtig te maken
// De boom zal alle knopen tussen 0 en 15 bevatten, toegevoegd in random volgorde
TEST_CASE("Zoekboom evenwichtig maken", "[eenvoudig]") {
    ZoekBoom<int, int> boom;
    vulZoekboom(boom, 15);
    boom.maakEvenwichtig();

    // diepte, wortel en aantal knopen controleren
    REQUIRE(boom.aantalKnopen() == 15);
    REQUIRE(boom->sleutel == 8);
    REQUIRE(boom.geefDiepte() == 4);
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}

//Test voor een gewone zoekboom evenwichtig te maken
// De boom zal alle knopen tussen 0 en 15 bevatten, toegevoegd in random volgorde
TEST_CASE("Zoekboom onevenwichtig maken", "[eenvoudig]") {
    ZoekBoom<int, int> boom;
    vulZoekboom(boom, 15);
    boom.maakOnevenwichtig();

    // diepte en aantal knopen controleren
    REQUIRE(boom.aantalKnopen() == 15);
    REQUIRE(boom.geefDiepte() == 15);
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}

// Een evenwichtige zoekboom met 15 knopen wordt aangemaakt waarna enkele knopen verwijderd worden.
TEST_CASE("Evenwichtige zoekboom verwijderen", "[verwijderen]") {

    // aanmaken boom
    ZoekBoom<int, int> boom;
    int toe_te_voegen[15] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 11, 9, 14, 13, 15};
    for (int i : toe_te_voegen) {
        boom.voegtoe(i, 0);
    }
    REQUIRE(boom.aantalKnopen() == 15); //boom juist aangemaakt?

    // verwijderen van 11 knopen:
    int te_verwijderen[11] = {7, 8, 2, 1, 4, 3, 6, 5, 11, 13, 15};
    for (int i : te_verwijderen) {
        boom.verwijder(i);
    }

    //juiste aantal knopen over ?
    REQUIRE(boom.aantalKnopen() == 4);
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}