#pragma once

#include <string>
#include "fietsnet.h"


std::string geojson(const KnooppuntGraaf &g);

std::string graaf_zoek_stappen_json(std::vector<GraafZoekStap> stappen);