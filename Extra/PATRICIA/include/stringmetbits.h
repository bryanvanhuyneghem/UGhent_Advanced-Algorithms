#ifndef __STRINGMETBITS_H
#define __STRINGMETBITS_H
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>
using std::string;

/**********************************************************************

   Class: StringMetBits
   
   beschrijving: klasse van strings met bitbehandelingsmogelijkheden.
   Elke StringMetBits wordt impliciet aangevuld met oneindig veel 0-bits en kan dus geen
   prefix zijn van een andere StringMetBits. Wel zou het karakter char(0) achteraan
   tot problemen leiden.
   Een StringMetBits mag dan ook het karakter char(0) niet bevatten en dit wordt gecheckt
   in de constructor, maar niet in wijzigingsoperatoren.
   
***************************************************************************/

class StringMetBits: public string{
public:
    StringMetBits(const string& str);
    StringMetBits(const StringMetBits& str);
    StringMetBits(const char* str="");
    void check0();
    
    int geefAantalBits() const;
    bool bit(int i) const;
    int verschilplaats(const StringMetBits& sb) const; //geeft -1 terug als strings gelijk zijn, anders plaats van meest linkse verschilbit
};

StringMetBits::StringMetBits(const string& str):string(str){
    check0();
}
StringMetBits::StringMetBits(const StringMetBits& str):string(str){
    check0();
}

StringMetBits::StringMetBits(const char* str):string(str){
    check0();
}

void StringMetBits::check0(){
    for (int i=0; i<size(); i++ ){
        assert((*this)[i]!=char(0));
    }
}

bool StringMetBits::bit(int i) const{
    if (i>=size()*8)
        return false;
    else
        return ((*this)[i/8] & uint(1) <<(7 - (i%8)));
}

int StringMetBits::geefAantalBits() const{
    return size()*8;
}

int StringMetBits::verschilplaats(const StringMetBits& sb) const{
    int minlengte=std::min(size(),sb.size());
    int i=0;
    while (i< minlengte && (*this)[i]==sb[i])
        i++;
    int bitplaats=8*i;//plaats 1e bit in verschillend karakter
    if (i==minlengte && size()==sb.size())
        return -1;
    else{
    //while moet niet testen op overloop: er is een verschillende bit
        int bitplaats=8*i;//plaats 1e bit in verschillend karakter
        while (bit(bitplaats)==sb.bit(bitplaats)){
            bitplaats++;
        }
        return bitplaats;
    }
}


#endif

