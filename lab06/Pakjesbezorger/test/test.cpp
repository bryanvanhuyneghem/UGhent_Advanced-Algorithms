#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "pakjes.h"

#include <chrono>
using namespace std::chrono;

TEST_CASE("Pakjes", "[pakjes]")
{
	std::vector<int> voertuigen_grootte = {1, 4, 17, 18, 75};
	std::vector<int> v = {75, 18, 17, 4, 1, 21, 86, 90, 38, 115, 1515, 1516, 1517};
	std::vector<int> gevonden;
	std::vector<int> opl = {1, 1, 1, 1, 1, 2, 5, 5, 3, 4, 24, 24, 21};
	for (int i = 0; i < v.size(); i++)
	{
		int min_aantal = min_aantal_voertuigen_top_down(v[i], voertuigen_grootte);
		std::cout << "aantal voertuigen nodig voor " << v[i] << " pakjes: " << min_aantal << std::endl;
		std::cout << "OPLOSSING: " << v[i] << " pakjes: " << opl[i] << std::endl;
		gevonden.push_back(min_aantal);
	}
	for (int i = 0; i < v.size(); i++)
	{
		REQUIRE(gevonden[i] == opl[i]);
	}
			

}

//zonder bakfiets
TEST_CASE("Pakjes zonder bakfiets", "[pakjes]")
{
	std::vector<int> voertuigen_grootte = {1, 17, 18, 75};
	std::vector<int> v = {75, 18, 17, 4, 1, 21, 86, 90, 38, 115, 1515, 1516, 1517};
	std::vector<int> opl = {1, 1, 1, 4, 1, 4, 5, 5, 4, 7, 24, 25, 21};
	for (int i = 0; i < v.size(); i++)
	{
		int min_aantal = min_aantal_voertuigen(v[i], voertuigen_grootte);
		std::cout << "aantal voertuigen nodig voor " << v[i] << " pakjes: " << min_aantal << std::endl;
		REQUIRE(min_aantal == opl[i]);
	}
}

TEST_CASE("Geen voertuigen of geen pakjes", "[fout]")
{
	std::vector<int> voertuigen_grootte1;
	REQUIRE(min_aantal_voertuigen(10, voertuigen_grootte1) == -1);
	voertuigen_grootte1 = {1, 17, 18, 75};
	REQUIRE(min_aantal_voertuigen(0, voertuigen_grootte1) == 0);
}

// test met timings van execution om recursie er uit te halen
// het kan zijn dat de test foutief af gaat
TEST_CASE("Niet recursief pakjes", "[experimenteel]")
{
	std::vector<int> voertuigen_grootte = {1, 17, 18, 75};

	auto t0 = high_resolution_clock::now();

	BENCHMARK("Min aantal voertuigen 115")
	{
		int min_aantal = min_aantal_voertuigen(115, voertuigen_grootte);
		REQUIRE(min_aantal == 7);
	};

	auto t1 = high_resolution_clock::now();

	BENCHMARK("Min aantal voertuigen 86")
	{
		int min_aantal = min_aantal_voertuigen(86, voertuigen_grootte);
		REQUIRE(min_aantal == 5);
	};

	auto t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t1 - t0);
	std::cout << std::endl << duration.count() << " µs" << std::endl;
	auto duration2 = duration_cast<microseconds>(t2 - t1);
	std::cout << duration2.count() << " µs" << std::endl;
	REQUIRE(duration.count() < 2 * duration2.count());
}


TEST_CASE("opgave2", "[experimenteel]")
{
	std::vector<int> getallen(101);
    std::iota(getallen.begin(), getallen.end(), 0);

	std::vector<int> optie1 = {1,4,9,17,18,75};
	std::vector<int> optie2 = {1,4,10,17,18,75};
	std::vector<int> optie3 = {1,4,17,18,35,75};
	std::vector<int> optie1_min(101);
	std::vector<int> optie2_min(101);
	std::vector<int> optie3_min(101);
	auto t0 = high_resolution_clock::now();

	BENCHMARK("bottom_up")
	{	
		for(int g : getallen){
			optie1_min[g] = min_aantal_voertuigen(g, optie1);
			optie2_min[g] = min_aantal_voertuigen(g, optie2);
			optie3_min[g] = min_aantal_voertuigen(g, optie3);
		}
		
	};
	auto t1 = high_resolution_clock::now();
	BENCHMARK("top_down")
	{

		for(int g : getallen){
			optie1_min[g] = min_aantal_voertuigen_top_down(g, optie1);
			optie2_min[g] = min_aantal_voertuigen_top_down(g, optie2);
			optie3_min[g] = min_aantal_voertuigen_top_down(g, optie3);
		}
			
		
	};
	
	auto t2 = high_resolution_clock::now();

	BENCHMARK("gestolen")
	{

		for(int g : getallen){
			optie1_min[g] = min_aantal_voertuigen_GESTOLEN(g, optie1);
			optie2_min[g] = min_aantal_voertuigen_GESTOLEN(g, optie2);
			optie3_min[g] = min_aantal_voertuigen_GESTOLEN(g, optie3);
		}
			
		
	};
	
	auto t3 = high_resolution_clock::now();
	

	std::vector<int> winnaars(101);
	for(int g : getallen){
		if(optie1_min[g] < optie2_min[g]){
			if(optie1_min[g] < optie3_min[g]){
				winnaars[g] = 1;
			}
			else if(optie3_min[g] < optie2_min[g]){
				winnaars[g] = 3;
			}
			else {
				winnaars[g] = 2;
			}
		}
		else if(optie3_min[g] < optie2_min[g]){
			winnaars[g] = 3;
		}
		else {
			winnaars[g] = 2;
		}
	}
	std::cout << "\noptie1: " << std::count(winnaars.begin(), winnaars.end(), 1) 
				<< "\noptie2: " << std::count(winnaars.begin(), winnaars.end(), 2) 
				<< "\noptie3: " << std::count(winnaars.begin(), winnaars.end(), 3)
				<< std::endl;

	auto duration = duration_cast<microseconds>(t1 - t0);
	std::cout << std::endl << "bottom up: " <<  duration.count() << " µs" << std::endl;
	auto duration2 = duration_cast<microseconds>(t2 - t1);
	std::cout << "top down: "<< duration2.count() << " µs" << std::endl;
	auto duration3 = duration_cast<microseconds>(t3 - t2);
	std::cout << "tGESTOLEN: "<< duration3.count() << " µs" << std::endl;

}
