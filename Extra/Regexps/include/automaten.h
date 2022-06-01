#include "regexp.h"

class NA
{
public:
    NA(const Regexp &);

private:
    // Datastructuur te bepalen
};

class DA
{
public:
    DA(const Regexp &);
    DA(const NA &);
    
    bool zitInTaal(const string &);

private:
    // Datastructuur te bepalen
};

