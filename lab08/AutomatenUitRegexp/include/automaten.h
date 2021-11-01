#ifndef AUTOMATEN_H
#define AUTOMATEN_H

#include <set>
#include <vector>
#include <map>
#include "regexp.h"
#include "na.h"
class DA {
    public:
    DA(const Regexp &);
    void convertNAToDA(const NA& na);

    std::vector<std::vector<int>> overgangstabel;
    std::map<char, int> symbols;
    std::set<int> terminaleStaten;

    bool zitInTaal(const string&);
    void epsilonSluiting(const NA& na, std::set<int>& staat);
    std::set<int> bereikbaarViaSymbolUitOudeStaat(const NA& na, std::set<int>& oude_staat, char symbol);

    void bereikbaarViaSymbolRec(const NA& na, std::set<int>& staat, int from, char symbol);
};
#endif