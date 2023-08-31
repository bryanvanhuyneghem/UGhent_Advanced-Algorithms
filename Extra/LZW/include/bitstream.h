#pragma once 

#include <sstream>
#include <string>
using std::istringstream;
using std::ostringstream;
using std::string;
typedef unsigned int uint;
typedef unsigned char uchar;

class ibitstream :public istringstream{
public:
    ibitstream(const string& s);
    void close();
    bool fail();

    bool eof();

    bool leesbit();

    uint32_t leesbits(uint num_bits);
    uint leesbyte();

private:
    bool eof_=false;
    char inchar;
    uint bits_verwerkt; //aantal verwerkte bits van laatst ingelezen byte

    uint32_t leesbits_(uint num_bits, uint32_t accum);
};

class obitstream : public ostringstream
{
public:
    obitstream();
    void close();
    bool fail();
    //Opletten: het werkelijke uitschrijven gbeurt in groepen van acht
    //gebruik flush om overgebleven bits uit te schrijven.
    //na een flush mag schrijfbit niet meer gebruikt worden!
    void schrijfbits(uint32_t bits, uint numbits);
    void schrijfbit(bool bit);
    void schrijfbyte(uint byte);
    void flush();

private:
    uint32_t uitbuffer; // een buffer van 4 karakters
    uint bits_gebruikt;
};