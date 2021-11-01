#pragma once
#include <string>
#include <vector>
#include "splayboom.h"

namespace landen
{
    struct wedstrijd
    {
        std::string thuisploeg;
        std::string bezoekers;
        int thuisscore;
        int bezoekersscore;
        std::string winnaar;
    };
} // namespace landen

std::vector<landen::wedstrijd> readCSV(const std::string &bestandsnaam);

Splayboom<string, int> doelpunten(std::vector<landen::wedstrijd> wedstrijden);

Splayboom<string, int> overwinningen(std::vector<landen::wedstrijd> wedstrijden);