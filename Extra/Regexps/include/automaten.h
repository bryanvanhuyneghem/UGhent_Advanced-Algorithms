#include "regexp.h"
#include <map>
#include <vector>
#include <set>
#include <ostream>
using std::map;
using std::multimap;
using std::set;
using std::vector;
using std::ostream;

constexpr uchar epsilon = 0;
constexpr int NA_START_TOESTAND = 0;
constexpr int NA_EIND_TOESTAND = 1;

class NA
{
public:
    NA(const Regexp &);

    /**
     * Een lijst van toestanden, waarbij index wordt gebruikt om ze te identificeren. 
     * Elke toestand heeft een map die karakters mapt op andere toestands-indices.
     * 
     * index 0 = begintoestand
     * index 1 = eindtoestand
     */
    vector<multimap<uchar, int>> toestanden;

    set<int> geefEpsilonSluiting(set<int> start_nrs) const;
    set<int> geefOvergangen(set<int> toestand_nrs, uchar karakter) const;

private:
    void voegToe(const Regexp &, int begin_nr, int eind_nr);
};

class DA
{
    friend ostream& operator<<(ostream &, const DA&);
public:
    DA(const Regexp &);
    DA(const NA &);

    bool zitInTaal(const string &);

private:
    struct DAToestand
    {
        bool eindToestand;
        map<uchar, int> overgangen;
    };

    // 0: begintoestand
    vector<DAToestand> toestanden;
};

