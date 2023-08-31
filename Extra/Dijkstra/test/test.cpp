#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "fietsnet.h"
#include <vector>
using std::vector;

TEST_CASE("Kortste Pad")
{
    const auto &[graaf, geoid_naar_knoopnr] = leesGraaf();
    vector<int> permanente_knoopnrs;

    SUBCASE("Van 9371 naar 827")
    {
        auto resultaat = kortstePad(graaf, geoid_naar_knoopnr.at(9371), geoid_naar_knoopnr.at(827), permanente_knoopnrs);
        REQUIRE(resultaat.size() == 2);
    }

    SUBCASE("Van 1006250 naar 4079085")
    {
        auto resultaat = kortstePad(graaf, geoid_naar_knoopnr.at(1006250), geoid_naar_knoopnr.at(4079085), permanente_knoopnrs);
        REQUIRE(resultaat.size() == 108);
    }

    SUBCASE("Van 1006250 naar 1007884")
    {
        auto resultaat = kortstePad(graaf, geoid_naar_knoopnr.at(1006250), geoid_naar_knoopnr.at(1007884), permanente_knoopnrs);
        auto resultaat2 = kortstePad(graaf, geoid_naar_knoopnr.at(1007884), geoid_naar_knoopnr.at(1006250), permanente_knoopnrs);
        REQUIRE(resultaat.size() == resultaat2.size());
        REQUIRE(resultaat.back().totale_afstand == doctest::Approx(resultaat2.back().totale_afstand));
    }
}

TEST_CASE("Bidirectioneel")
{
    const auto &[graaf, geoid_naar_knoopnr] = leesGraaf();
    vector<int> permanente_knoopnrs;
    
    SUBCASE("Van 9371 naar 827")
    {
        auto resultaatBiDir = kortstePadBidirectioneel(graaf, geoid_naar_knoopnr.at(9371), geoid_naar_knoopnr.at(827), permanente_knoopnrs);
        auto resultaatUniDir = kortstePad(graaf, geoid_naar_knoopnr.at(9371), geoid_naar_knoopnr.at(827), permanente_knoopnrs);
        REQUIRE(resultaatBiDir == resultaatUniDir);

    }

    SUBCASE("Van 1006250 naar 4079085")
    {
        auto resultaat = kortstePadBidirectioneel(graaf, geoid_naar_knoopnr.at(1006250), geoid_naar_knoopnr.at(4079085), permanente_knoopnrs);
        REQUIRE(resultaat.size() == 108);
    }

    SUBCASE("Van 1006250 naar 1007884")
    {
        auto resultaat = kortstePadBidirectioneel(graaf, geoid_naar_knoopnr.at(1006250), geoid_naar_knoopnr.at(1007884), permanente_knoopnrs);
        auto resultaat2 = kortstePadBidirectioneel(graaf, geoid_naar_knoopnr.at(1007884), geoid_naar_knoopnr.at(1006250), permanente_knoopnrs);
        REQUIRE(resultaat.size() == resultaat2.size());
        REQUIRE(resultaat.back().totale_afstand == doctest::Approx(resultaat2.back().totale_afstand));
    }
}
