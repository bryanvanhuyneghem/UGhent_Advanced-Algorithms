#include "automaten.h"
#include <deque>
#include <set>
#include <vector>
#include <algorithm>
using std::deque;
using std::for_each;
using std::set;
using std::vector;

NA::NA(const Regexp &regexp) : toestanden(2) //0=begintoestand, 1=eindtoestand
{
    voegToe(regexp, 0, 1);
}

void NA::voegToe(const Regexp &regexp, int begin_nr, int eind_nr)
{

    switch (regexp.geefOpcode())
    {
    case Regexp::letter:
        toestanden[begin_nr].insert({regexp.geefLetter(), eind_nr});
        return;
    case Regexp::concatenatie:
    {
        int tussen_nr = toestanden.size();
        toestanden.resize(toestanden.size() + 1);
        voegToe(*regexp.geefEersteOperand(), begin_nr, tussen_nr);
        voegToe(*regexp.geefTweedeOperand(), tussen_nr, eind_nr);
    }
        return;
    case Regexp::of:
        voegToe(*regexp.geefEersteOperand(), begin_nr, eind_nr);
        voegToe(*regexp.geefTweedeOperand(), begin_nr, eind_nr);
        return;

    case Regexp::ster:
    {
        int in_nr = toestanden.size();
        int uit_nr = in_nr + 1;
        toestanden.resize(toestanden.size() + 2);

        toestanden[begin_nr].insert({epsilon, in_nr});
        toestanden[in_nr].insert({epsilon, eind_nr});
        toestanden[uit_nr].insert({epsilon, in_nr});

        voegToe(*regexp.geefEersteOperand(), in_nr, uit_nr);
    }
        return;
    }
}

set<int> NA::geefEpsilonSluiting(set<int> start_nrs) const
{
    deque<int> te_onderzoeken(start_nrs.begin(), start_nrs.end());

    set<int> esluiting(start_nrs);
    while (!te_onderzoeken.empty())
    {
        int t_nr = te_onderzoeken.front();
        te_onderzoeken.pop_front();

        auto [eps_begin, eps_end] = toestanden[t_nr].equal_range(epsilon);

        std::for_each(eps_begin, eps_end, [&](auto pair) {
            te_onderzoeken.push_back(pair.second);
            esluiting.insert(pair.second);
        });
    }

    return esluiting;
}

set<int> NA::geefOvergangen(set<int> toestand_nrs, uchar karakter) const
{
    set<int> nieuwe_toestanden;
    for (int toestand_nr : toestand_nrs)
    {
        auto [kar_begin, kar_end] = toestanden[toestand_nr].equal_range(karakter);

        std::for_each(kar_begin, kar_end, [&](auto pair) {
            nieuwe_toestanden.insert(pair.second);
        });
    }

    return nieuwe_toestanden;
}

DA::DA(const Regexp &regexp) : DA(NA(regexp)) {}

DA::DA(const NA &na)
{
    deque<set<int>> teOnderzoekenToestanden;
    map<set<int>, int> nieuwe_toestand_nrs;
    int volgende_nieuwe_toestand_nr = 0;

    set<int> startToestand = na.geefEpsilonSluiting({NA_START_TOESTAND});
    nieuwe_toestand_nrs[startToestand] = volgende_nieuwe_toestand_nr++;
    toestanden.resize(volgende_nieuwe_toestand_nr);
    teOnderzoekenToestanden.push_back(startToestand); //starttoestand

    while (!teOnderzoekenToestanden.empty())
    {
        set<int> tNrSet = teOnderzoekenToestanden.front();
        teOnderzoekenToestanden.pop_front();

        DAToestand *dat = &toestanden[nieuwe_toestand_nrs[tNrSet]];
        toestanden[nieuwe_toestand_nrs[tNrSet]].eindToestand = tNrSet.find(NA_EIND_TOESTAND) != tNrSet.end();

        //bepaal alle unieke overgangen (=karakters) vanuit deze set
        set<uchar> uniekeOvergangen;

        for (int tNr : tNrSet)
        {
            for (auto [key, buur_nr] : na.toestanden[tNr])
            {
                uniekeOvergangen.insert(key);
            }
        }
        uniekeOvergangen.erase(epsilon);
        //bepaal voor alle unieke overgangen de volgende buur
        for (uchar c : uniekeOvergangen)
        {
            set<int> buurToestand = na.geefEpsilonSluiting(na.geefOvergangen(tNrSet, c));

            if (nieuwe_toestand_nrs.find(buurToestand) == nieuwe_toestand_nrs.end())
            {
                nieuwe_toestand_nrs[buurToestand] = volgende_nieuwe_toestand_nr++;
                toestanden.resize(volgende_nieuwe_toestand_nr);
                teOnderzoekenToestanden.push_back(buurToestand);
            }
            toestanden[nieuwe_toestand_nrs[tNrSet]].overgangen[c] = nieuwe_toestand_nrs[buurToestand];
        }
    }
}

bool DA::zitInTaal(const string &s)
{
    DAToestand *huidigeToestand = &toestanden[0]; // 0 bevat altijd de starttoestand

    for (uchar c : s)
    {
        auto pos = huidigeToestand->overgangen.find(c);
        if (pos == huidigeToestand->overgangen.end())
        {
            return false;
        }
        huidigeToestand = &toestanden[pos->second];
    }

    return huidigeToestand->eindToestand;
}

ostream & operator<<(ostream& os, const DA & da)
{

    os << "digraph {\n";
    os << "\t rankdir=\"LR\";\n" ;

    for(int i = 0; i < da.toestanden.size(); i++){
        const DA::DAToestand *dat = &da.toestanden[i];

        if(dat->eindToestand){
            os << "\t " << i << " [shape=square];\n";
        }
        for(auto [karakter, buur_nr] : dat->overgangen){
            os << "\t " << i << " -> " << buur_nr << " [label=\"";
            if(karakter != epsilon){
                os << karakter;
            }else {
                os << "ε";
            } 
            os << "\"];\n";
        }
    }

    os << "}\n";

    return os;
}
