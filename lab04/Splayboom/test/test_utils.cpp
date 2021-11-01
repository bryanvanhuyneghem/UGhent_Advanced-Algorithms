#include <algorithm>
#include "zoekknoop.h"
#include "test_utils.h"

/**
* Vul zoekboom met alle knopen tussen 1 en grootte (inclusief)
*/
void vulZoekboom(ZoekBoom<int, int> &boom, int grootte) {
   assert(boom.aantalKnopen() == 0);

   //genereer een vector nummers tussen 1 en `grootte` in random volgorde
   std::random_device rd;
   std::mt19937 gen(rd());

   std::vector<int> nummers(grootte);
   for (int i = 0; i < grootte; ++i) {
       nummers[i] = i + 1;
   }
   std::shuffle(nummers.begin(), nummers.end(), gen);


   std::uniform_int_distribution<int> data_distributie(1, grootte);
   for (int nummer : nummers) {
       boom.voegtoe(nummer, data_distributie(gen));
   }
   if (boom.aantalKnopen() != grootte) {
       throw std::runtime_error("Aantal knopen in boom is minder dan het aantal toegevoegde knopen");
   }
}
