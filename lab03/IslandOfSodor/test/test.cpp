#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "network-reader.h"
#include "sodor.h"

using sodor::Destination;
using sodor::TrainStation;
TEST_CASE("Simpel treinnetwerk", "[sodor]")
{

	std::vector<TrainStation> stations;

	for (int i = 0; i < 9; ++i)
	{
		TrainStation ts;
		ts.name = std::to_string(i);
		stations.push_back(ts);
	}

	auto addConnection = [&stations](int van, int naar){
		Destination ds;
		ds.name = std::to_string(naar);
		stations[van].destinations.push_back(ds);
	};

	int verbindingen[14][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 4}, {2, 4}, {2, 5}, {3, 5}, {4, 6}, {4, 7}, {5, 7}, {5, 8}, {6, 9}, {7, 9}, {8, 9}};
	for (auto [van, naar] : verbindingen)
	{
		addConnection(van,naar);
	}
	CHECK(zoekMinimaleStationsluitingen(stations, "0", "9") == 2);

	addConnection(3,4);
	CHECK(zoekMinimaleStationsluitingen(stations, "0", "9") == 2);

	addConnection(1,6);
	CHECK(zoekMinimaleStationsluitingen(stations, "0", "9") == 3);

	addConnection(3,8);
	CHECK(zoekMinimaleStationsluitingen(stations, "0", "9") == 3);

}

TEST_CASE("Read network", "[sodor]")
{
	auto stations = readNetwork("../sodor-trainnetwork.json");

	CHECK(stations.size() == 180);
}
