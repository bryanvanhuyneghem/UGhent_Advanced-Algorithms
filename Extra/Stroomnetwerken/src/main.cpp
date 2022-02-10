#include <iostream>
#include "galadiner.h"

void print_tafelverdeling(vector<vector<int>> tafelverdeling) {
  std::cout << "Tafelverdeling:\n";
  for (auto tafel : tafelverdeling) {
    for (int delegatie : tafel) {
      std::cout << delegatie << " ";
    }
    std::cout << '\n';
  }
  std::cout << "\n";
}

int main() {
  
  print_tafelverdeling(zoek_tafelverdeling({1,1,2},{2,2}));

  // print_tafelverdeling(zoek_tafelverdeling({5, 5, 3, 6, 2}, {3, 4, 4, 5, 5, 5}));

}
