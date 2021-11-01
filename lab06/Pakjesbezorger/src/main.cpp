#include <vector>
#include <iostream>

#include <chrono>
#include <numeric>
#include <random>
using namespace std::chrono;

#include "pakjes.h"

int main(int argc, char** argv) {
	
	std::vector<int> voertuigen_grootte = {1,17,18,75};
	std::vector<int> v = {75,18,17,4,1,21,86,90,38,115,1515,1516,1517, 22000}; 
	int s = 0;
	for(int g: v){
		s += min_aantal_voertuigen_top_down(g, voertuigen_grootte);
	}
	return s;
}