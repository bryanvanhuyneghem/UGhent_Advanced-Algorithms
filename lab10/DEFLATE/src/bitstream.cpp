#include "bitstream.h"

ibitstream::ibitstream(const string &s) : istringstream(s), bits_verwerkt(8)
{
}

bool ibitstream::fail()
{
    return istringstream::fail();
}

bool ibitstream::eof()
{
    if(!eof_ && bits_verwerkt == 8){
        bits_verwerkt = 0;
        eof_ = !get(inchar);
    }
    return eof_;
}

uint32_t ibitstream::leesbits(uint numbits)
{
    return leesbits_(numbits, 0);
}

uint32_t ibitstream::leesbits_(uint numbits, uint32_t accum)
{
    if (numbits == 0)
        return accum;

    if (bits_verwerkt == 8)
    {
        eof_ = !get(inchar);
        bits_verwerkt = 0;
    }

    uint bits_over = 8 - bits_verwerkt;

    uint te_lezen_bits = bits_over > numbits ? numbits : bits_over;
    accum <<= te_lezen_bits;

    uint16_t mask = (1U << te_lezen_bits) - 1;
    uint off = 8 - bits_verwerkt - te_lezen_bits;

    accum |= (inchar & (mask << off)) >> off;
    bits_verwerkt += te_lezen_bits;

    return leesbits_(numbits - te_lezen_bits, accum);
}

bool ibitstream::leesbit()
{
    return leesbits(1) != 0;
}

uint ibitstream::leesbyte()
{
    return leesbits(8);
}

obitstream::obitstream() : bits_gebruikt(0), uitbuffer(0)
{
}

void obitstream::close()
{
    flush();
}

bool obitstream::fail()
{
    return ostringstream::fail();
}

void obitstream::schrijfbits(uint32_t bits, uint num_bits)
{
    //zet alle andere bits na num_bits laatste op 0
    bits &= (1U << num_bits) - 1;

    uitbuffer = (uitbuffer << num_bits) | bits;
    bits_gebruikt += num_bits;

    while (bits_gebruikt >= 8)
    {
        //we kunnen een karakter wegschrijven
        uchar volgende_char = (uitbuffer >> (bits_gebruikt - 8)) & (1U << 8) - 1; //zorgen dat er zeker niets beduidens achter pos 9 staat
        put(volgende_char);
        bits_gebruikt -= 8;
    }
}

void obitstream::schrijfbit(bool bit)
{
    schrijfbits((uint)bit, 1);
}

void obitstream::schrijfbyte(uint byte)
{
    schrijfbits(byte, 8);
}
void obitstream::flush()
{
    schrijfbits(0, 8 - bits_gebruikt);
}