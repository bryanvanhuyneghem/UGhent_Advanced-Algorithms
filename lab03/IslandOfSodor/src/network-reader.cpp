#include <nlohmann/json.hpp>
#include <fstream>
#include "network-reader.h"

using json = nlohmann::json;

namespace sodor
{
  

    /* The following two lines call a macro that generates the
       to_json/from_json functions needed to enable direct conversion
       from a JSON-file to these structs.

       cfr. https://github.com/nlohmann/json#arbitrary-types-conversions
    */

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Destination, name, distance);
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TrainStation, name, description, x, y, elevation, destinations);
} // namespace sodor

std::vector<sodor::TrainStation> readNetwork(const std::string &filename)
{
    std::ifstream f;
    f.open(filename);

    json j;
    f >> j;

    auto stations = j.get<std::vector<sodor::TrainStation>>();

    f.close();

    return stations;
}