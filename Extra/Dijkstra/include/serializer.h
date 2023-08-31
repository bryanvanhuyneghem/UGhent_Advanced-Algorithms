#pragma once

#include <string>
#include "fietsnet.h"


std::string geojson(const KnooppuntGraaf &g);

std::string graaf_kortste_pad_json(const KnooppuntGraaf &g, const std::list<KortstePadStap>& stappen);

std::string permanente_knopen_json(const KnooppuntGraaf &g, const std::vector<int>& knoopnrs);