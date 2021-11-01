#include <vector>
#include <limits>
#include <iostream>

#include <cstdlib>
int min_aantal_voertuigen(int aantal_pakjes, const std::vector<int>& voertuigen_grootte);
int min_aantal_voertuigen_top_down(int aantalPakjes, const std::vector<int>& voertuigen_grootte);
int min_aantal_voertuigen_GESTOLEN(int aantalPakjes, const std::vector<int> &voertuigen_grootte);
int top_down_impl(std::vector<int>& min_v, const std::vector<int>& voertuigen_grootte, int aantal);
