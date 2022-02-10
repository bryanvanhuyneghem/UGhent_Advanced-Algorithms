#include "automaten.h"

NA::NA(const Regexp &regexp)
{
    
}



DA::DA(const Regexp &regexp) : DA(NA(regexp)) {}

DA::DA(const NA &na)
{

}

bool DA::zitInTaal(const string &s)
{
    return false;
}
