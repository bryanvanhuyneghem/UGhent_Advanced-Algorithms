#pragma once
#include <string>
#include <vector>

namespace sodor
{
    struct Destination
    {
        std::string name;
        double distance;
    };

    struct TrainStation
    {
        std::string name;
        std::string description;
        double x, y, elevation;
        std::vector<Destination> destinations;
    };
} // namespace sodor

std::vector<sodor::TrainStation> readNetwork(const std::string& filename);