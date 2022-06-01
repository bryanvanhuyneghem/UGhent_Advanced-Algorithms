#include "csv.hpp"
#include "fietsnet.h"

int main() {
  auto g = leesGraaf();
  std::cout << "Ingelezen graaf bevat " << g.aantalKnopen() << " knopen en "
            << g.aantalVerbindingen() << " verbindingen.\n";

  auto g2 = reduceerGraaf(g);
  std::cout << "Gereduceerde graaf bevat " << g2.aantalKnopen() << " knopen en "
            << g2.aantalVerbindingen() << " verbindingen.\n";

  return 0;
}
