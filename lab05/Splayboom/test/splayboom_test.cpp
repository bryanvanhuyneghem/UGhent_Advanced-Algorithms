#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include <catch2/catch.hpp>
#include "splayboom.h"
#include "leeslanden.h"
#include "test_utils.h"

// test voor het toevoegen van 10 knopen in een splayboom
TEST_CASE("Toevoegen aan splayboom", "[eenvoudig]") {
    Splayboom<int, int> boom;
    int points[10] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10};
    for (int i : points) {
        boom.voegtoe(i, 2);
    }
    REQUIRE(boom.aantalKnopen() == 10);
    REQUIRE(boom.get()->sleutel == 10);
    REQUIRE(boom.geefDiepte() == 8);
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}

// test voor zoeken in splayboom (voegtoe is een vereiste)
TEST_CASE("Zoeken in splayboom", "[eenvoudig]") {
    Splayboom<int, int> boom;
    int points[10] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10};
    for (int i : points) {
        boom.voegtoe(i, 0);
    }
    REQUIRE(boom.aantalKnopen() == 10);
    for (int i = 2; i < 7; i++) {
        boom.zoekSleutel(i);
        REQUIRE(boom.get()->sleutel == i);
    }

    boom.zoekSleutel(20);
    REQUIRE(boom.get()->sleutel == 12);
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}

// test voor zoeken in splayboom met 10 knopen die random is opgesteld
TEST_CASE("Random boom", "[Random]") {
    Splayboom<int, int> boom;
    vulZoekboom(boom, 10);
    REQUIRE(boom.aantalKnopen() == 10);
    for (int i = 2; i < 7; i++) {
        boom.zoekSleutel(i);
        REQUIRE(boom.get()->sleutel == i);
    }
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}

// Test toepassing doelpunten
TEST_CASE("Toepassing doelpunten", "[Toepassing]") {
    auto wedstrijden = readCSV("voetbal_resultaten.csv");

    Splayboom<std::string, int> doelp = doelpunten(wedstrijden);

    doelp.zoekSleutel("France");

    REQUIRE(doelp.get()->sleutel == "France");
    REQUIRE(doelp.get()->geefData() == 1498);
    REQUIRE_NOTHROW(repOKZoekboom(doelp));
}

// Test toepassing overwinningen
TEST_CASE("Toepassing overwinningen", "[Toepassing]") {
    auto wedstrijden = readCSV("voetbal_resultaten.csv");

    Splayboom<std::string, int> winsten = overwinningen(wedstrijden);

    winsten.zoekSleutel("Belgium");

    REQUIRE(winsten.get()->sleutel == "Belgium");
    REQUIRE(winsten.get()->geefData() == 335);
    REQUIRE_NOTHROW(repOKZoekboom(winsten));
}

// Verwijderen in splayboom (voegtoe is vereiste)
TEST_CASE("Splayboom verwijderen", "[verwijderen]") {
    // constructie boom
    Splayboom<int, int> boom;
    int points2[10] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10};
    for (int i : points2) {
        boom.voegtoe(i, 0);
    }
    REQUIRE(boom.aantalKnopen() == 10);

    // verwijderen van 4 knopen
    int point1[4] = {3, 6, 5, 4};
    for (int i : point1) {
        boom.verwijder(i);
    }

    // controle aantal knopen
    REQUIRE(boom.aantalKnopen() == 6);
    REQUIRE_NOTHROW(repOKZoekboom(boom));
}
