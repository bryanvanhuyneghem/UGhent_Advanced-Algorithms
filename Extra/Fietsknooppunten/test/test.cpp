#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
#include <catch2/catch.hpp>

#include "fietsnet.h"

TEST_CASE("Graaf inlezen", "[fietsnet]") {
  KnooppuntGraaf g = leesGraaf();

  REQUIRE(g.aantalKnopen() == 3982);
  REQUIRE(g.aantalVerbindingen() == 5940);
}

TEST_CASE("Graaf reduceren", "[fietsnet]") {
  KnooppuntGraaf g = leesGraaf();

  KnooppuntGraaf g2 = reduceerGraaf(g);

  REQUIRE(g2.aantalKnopen() / g.aantalKnopen() < 0.95);
  REQUIRE(g2.aantalVerbindingen() / g.aantalVerbindingen() < .965);
}
