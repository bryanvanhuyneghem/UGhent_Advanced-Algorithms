#include "kerstman.h"
#include "kerstman_sa.h"
#include "kerstman_prob.h"
#include "simulatedannealing.h"
#include <vector>
#include <iostream>

void printVector(std::vector<int> v)
{
  std::cout << "{";
  for (auto i : v)
  {
    std::cout << i << ", ";
  }
  std::cout << "}" << std::endl;
}

int main()
{
  vector<vector<double>> afst = berekenAfstanden();
  double optimumF;

  if(afst.size() == 0) 
    throw std::runtime_error("fout bij inlezen");
  // 1. Probabilistiche werkwijze
  srand(time(0));
  kerstman_prob tsppp(afst);
  vector<int> probOplossing = tsppp.geefOptimum(50);
  // printVector(probOplossing);
  std::cout << "De beste oplossing via ProbProb gevonden voor het probleem is: " << tsppp.f(probOplossing) << std::endl;
  
  
  // 2. random variant van oplossing construeren
  for(int i= 0; i<100; i++){
    tsppp.pickAtRandom(probOplossing);
  }
  std::cout << "De beste oplossing via ProbProb na wisselen van random knopen voor het probleem is: " << tsppp.f(probOplossing) << std::endl;
  // 3. oplossing lokaal gaan verbeteren
  tsppp.verbeterLokaal(probOplossing);
  std::cout << "De beste oplossing via ProbProb na lokaal verbeteren gevonden voor het probleem is: " << tsppp.f(probOplossing) << std::endl;

  // 4. simulated annealing
  kerstman_sa annealing(afst);
  vector<int> annealing_oplossing = annealing.oplossing();
  std::cout << "De beste oplossing gevonden via Simulated annealing voor het probleem is: " << annealing.f(annealing_oplossing) << std::endl;

  std::cout << "Done" << std::endl;
  return 0;
}