#include <string>
#include <math.h>
#include <stack>
#include <vector>
#include <list>
#include <forward_list>
#include <assert.h>
#include "graaf.hpp"
#include "euler.h"


std::string nummer_naar_string(int nr, int lengte_alfabet, int orde)
{
    char *c_str = new char[orde + 1];

    c_str[orde] = '\0';
    for (int plaats_nr = orde - 1; plaats_nr >= 0; --plaats_nr)
    {
        c_str[plaats_nr] = 'a' + (nr % lengte_alfabet);
        nr /= lengte_alfabet;
    }

    std::string s{c_str};
    delete[] c_str;

    return s;
}

std::string genereer_debruijnreeks(int lengte_alfabet, int orde)
{
   // VUL AAN
}
