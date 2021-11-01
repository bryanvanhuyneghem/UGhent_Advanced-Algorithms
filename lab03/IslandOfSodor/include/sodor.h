#pragma once

#include <string>
#include "network-reader.h"

/***
 * Geeft het aantal stations terug dat gesloten moet worden om
 * alle verbindingen tussen start-station en eind-station te verbreken
 */
int zoekMinimaleStationsluitingen(const std::vector<sodor::TrainStation> &stations,
                                  const std::string &startStationNaam, const std::string &eindStationNaam);