#pragma once
#include "bknoop.h"
#include <string>
#include <vector>

namespace hosts
{
    struct property
    {
        std::string name;
        std::string buurt; //neighbourhood
        int prijs;
        int aantalreviews;
        int beschikbaarheid;
    };
}

BTree<int, hosts::property, 10> leesCSV(const std::string &bestandsnaam, Schijf<BKnoop<int, hosts::property, 10>>* schijf);

BTree<int, int, 100> leesCSV_prijs(const std::string &bestandsnaam, Schijf<BKnoop<int, int, 100>>* schijf);
std::vector<std::string> readCSVRow(const std::string &row);
std::vector<std::vector<std::string>> readCSV(std::istream &in);