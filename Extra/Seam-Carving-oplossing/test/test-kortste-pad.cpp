#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
#include <catch2/catch.hpp>

#include "kortste-pad.h"


GraafMetTakdata<GERICHT,int> voorbeeldGraaf(){
  // graaf uit slides

    GraafMetTakdata<GERICHT, int> g(6);
    g.voegVerbindingToe(0,1,5);
    g.voegVerbindingToe(0,3,1);
    g.voegVerbindingToe(1,2,3);
    g.voegVerbindingToe(2,5,2);
    g.voegVerbindingToe(3,4,2);
    g.voegVerbindingToe(4,1,1);
    g.voegVerbindingToe(4,3,5);
    g.voegVerbindingToe(4,5,3);

    return g;
} 

TEST_CASE("Kortste pad voorbeeldgraaf", "[dijkstra]") {
  GraafMetTakdata<GERICHT,int> g = voorbeeldGraaf();
  std::list<int> pad = shortest_path(g, 0, 5);

  std::cout << "Kortste pad van 0 naar 5: ";
  for(int nr : pad ){
    std::cout << nr << " -> ";
  }
  std::cout << "\n";
}
