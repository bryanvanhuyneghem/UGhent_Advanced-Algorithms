#pragma once

#include "pugixml.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string.h>

using std::pair;
using std::vector;

//bezoekt een (deel)boom met een visitor in preorder
void DEZBezoekpre(pugi::xml_node n, std::function<void(pugi::xml_node)> bezoekKnoop);

vector<pair<double, double>> leesKnooppunten(pugi::xml_document &n);

vector<vector<double>> berekenAfstanden();