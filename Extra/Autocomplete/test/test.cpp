#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "ternaire-zoekboom.h"

TEST_CASE("Eenvoudige ternaire zoekboom") {
    TernaireZoekboom tz;

    string woorden[] = {"dit", "dat", "diets", "diesel", "differentiaal", "die"};
    for (string woord : woorden) {
        tz.voegtoe(woord);
    }

    REQUIRE(tz.zoek("dit"));
    REQUIRE(tz.zoek("die"));
    REQUIRE(tz.zoek("differentiaal"));
    REQUIRE_FALSE(tz.zoek("dik"));
    REQUIRE_FALSE(tz.zoek("diff"));
}

TEST_CASE("Autocomplete") {
    TernaireZoekboom tz;

    string woorden[] = {"dit", "dat", "diets", "diesel", "differentiaal", "die"};
    for (string woord : woorden) {
        tz.voegtoe(woord);
    }

    std::vector<string> auto_complete = tz.auto_complete("die");
    REQUIRE(auto_complete.at(0) == "die");
    REQUIRE(auto_complete.at(2) == "diets");
    REQUIRE(auto_complete.size() == 3);
}

TEST_CASE("Productcodes") {
    string productcodes[] = {"RD-R9250", "FD-R9250", "BT-DN300", "EW-EC300",
                             "CS-R9200", "BR-R9270", "ST-R9270"};

    TernaireZoekboom tz_productcodes;
    for (string code : productcodes) {
        tz_productcodes.voegtoe(code);
    }

    // het opsplitsen van de tekst over 2 lijnen vermijdt warnings over trigraphs
    // cfr. https://en.wikipedia.org/wiki/Digraphs_and_trigraphs#C
    std::vector<string> auto_complete_productcodes = tz_productcodes.auto_complete_wildcard("??"
                                                                                            "-R92");

    REQUIRE(auto_complete_productcodes.at(0) == "BR-R9270");
    REQUIRE(auto_complete_productcodes.at(2) == "FD-R9250");
    REQUIRE(auto_complete_productcodes.size() == 5);
}

TEST_CASE("Woordenboek") {
    std::ifstream woordenlijst("woordenlijst.txt");
    string woord;

    TernaireZoekboom tz;

    while (std::getline(woordenlijst, woord)) {
        tz.voegtoe(woord);
    }

    string te_zoeken = "algo";

    std::vector<string> auto_complete = tz.auto_complete(te_zoeken);

    REQUIRE(auto_complete.size() == 5);

    te_zoeken = "a";
    auto_complete = tz.auto_complete(te_zoeken);

    REQUIRE(auto_complete.size() == 11537);
}
