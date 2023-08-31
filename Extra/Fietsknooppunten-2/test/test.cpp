#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "fietsnet.h"

TEST_CASE("Graaf inlezen")
{
    const auto &[graaf, geoids] = leesGraaf();

    REQUIRE(graaf.aantalKnopen() == 3982);
    REQUIRE(graaf.aantalVerbindingen() == 5939);

    REQUIRE(geoids.size() == 3982);


    auto knp = graaf.geefKnoopdata(geoids.at(9371));
    REQUIRE(knp->naam == "Leiestreek");
    REQUIRE(knp->knoopnr == 2);

    REQUIRE(graaf.verbindingsnummer(geoids.at(9371), geoids.at(828)) > -1);
    REQUIRE(*graaf.geefTakdata(geoids.at(9371), geoids.at(828)) == doctest::Approx(2291.33));
}

TEST_CASE("Breedte Eerst Zoeken")
{
    const auto &[graaf, geoid_naar_knoopnr] = leesGraaf();

    SUBCASE("diepte 1")
    {
        auto resultaat = breedte_eerst_zoeken(graaf, geoid_naar_knoopnr.at(9371), 1);

        REQUIRE(resultaat.size() == 4);
    }

    SUBCASE("diepte 2")
    {
        auto resultaat = breedte_eerst_zoeken(graaf, geoid_naar_knoopnr.at(9371), 2);
        REQUIRE(resultaat.size() == 10);
    }

    SUBCASE("diepte 3")
    {
        auto resultaat = breedte_eerst_zoeken(graaf, geoid_naar_knoopnr.at(9371), 3);
        REQUIRE(resultaat.size() == 20);
    }
    SUBCASE("diepte 10")
    {
        auto resultaat = breedte_eerst_zoeken(graaf, geoid_naar_knoopnr.at(9371), 10);
        REQUIRE(resultaat.size() == 221);
    }

    SUBCASE("diepte 25")
    {
        auto resultaat = breedte_eerst_zoeken(graaf, geoid_naar_knoopnr.at(9371), 25);
        REQUIRE(resultaat.size() == 1279);
    }

    SUBCASE("diepte 50")
    {
        auto resultaat = breedte_eerst_zoeken(graaf, geoid_naar_knoopnr.at(9371), 50);
        REQUIRE(resultaat.size() == 2988);
    }
}
