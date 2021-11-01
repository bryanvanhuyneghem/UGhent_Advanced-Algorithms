#include <catch2/catch.hpp>
#include "stroomnet.h"

TEST_CASE("Eenvoudig stroomnetwerk", "[eenvoudig]")
{
  GraafMetTakdata<GERICHT, int> gr(8);
  gr.voegVerbindingToe(1, 2, 7);
  gr.voegVerbindingToe(7, 1, 2);
  gr.voegVerbindingToe(7, 3, 6);
  gr.voegVerbindingToe(3, 4, 7);
  gr.voegVerbindingToe(4, 5, 1);
  gr.voegVerbindingToe(2, 5, 4);
  gr.voegVerbindingToe(1, 0, 10);
  gr.voegVerbindingToe(0, 2, 3);
  gr.voegVerbindingToe(0, 7, 5);
  gr.voegVerbindingToe(0, 6, 6);
  gr.voegVerbindingToe(5, 6, 6);
  gr.voegVerbindingToe(3, 6, 2);
  gr.voegVerbindingToe(6, 4, 8);

  Pad<int> pad;
  Stroomnetwerk<int> sn(gr, 1, 4);

  Stroomnetwerk<int> stroom = sn.geefStroom();

  REQUIRE(stroom.geefCapaciteit() == 13);
}