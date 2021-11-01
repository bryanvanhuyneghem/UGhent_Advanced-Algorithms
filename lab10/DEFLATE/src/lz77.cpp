#include "lz77.h"

#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <iostream>
#include "bitstream.h"
#include "suffix_array.h"


const int WINDOW_SIZE = 15;
const int LOOKAHEAD_BUFFER_SIZE = 8;

const int OUTPUT_BUFFER_SIZE = 32;


std::string compress_lz77(const std::string &input)
{
    size_t cursor = 0;
    size_t input_size = input.size();

    int dictionary_size = pow(2, WINDOW_SIZE);           // (2^15 - 1) + 1 because p >= 1 if there is a match
    int buffer_size = pow(2, LOOKAHEAD_BUFFER_SIZE) + 2; // (2^8 - 1) + 3 because n >= 3

    SuffixArray sa(input);

    obitstream output;

    while (cursor < input_size)
    {
        // if cursor < dictionary_size then substr(0, cursor) else substr(cursor - dictionary_size, dictionary_size)
        int search_buffer_start = std::max(0, (int)cursor - dictionary_size);
        int search_buffer_lengte = std::min(cursor, (size_t)dictionary_size);
        int lookahead_buffer_lengte = std::min(buffer_size, (int)(input_size-cursor));

        int afstand; // in {1, ..., 2^15}, will be shifted to {0, ..., 2^15 - 1} ; 2^15 = 32768
        int lengte; // in {3, ..., 2^8 + 2}, will be shited to {0, ..., 2^8 - 1} ; 2^8 = 256

        std::tie(lengte, afstand) = sa.zoekHerhaling(search_buffer_start, search_buffer_lengte, lookahead_buffer_lengte);
        if (lengte < 3)
        {
            output.schrijfbit(0);
            output.schrijfbyte((unsigned char)input[cursor]);

            cursor++;
        }
        else
        {
            output.schrijfbit(1); // write a 1
            output.schrijfbits(afstand-1, WINDOW_SIZE);
            output.schrijfbits(lengte-3, LOOKAHEAD_BUFFER_SIZE);

            cursor += lengte;
        }
    }
    output.flush();
    return output.str();
}



std::string decompress_lz77(const std::string &input)
{
    ibitstream ibs(input);
    std::string output;

    while (!ibs.eof())
    {

        bool isLookback = ibs.leesbit();

        /**
        0: char van 8 bits lang
        1: tuple (afstand, lengte) op 15 + 8 bits (enkel als lengte >= 3, anders wordt het als gewone characters opgeslagen)
            nota: lengte werd met 1 verlaagd, afstand met 3
        */
        if (!isLookback)
        {
            unsigned char c =  (char)ibs.leesbyte();
            if( !ibs.eof()){
                output += c;
            }
        }
        else
        {
            int p = ibs.leesbits(WINDOW_SIZE) + 1;
            int n = ibs.leesbits(LOOKAHEAD_BUFFER_SIZE) + 3;

            size_t match_begin = output.size() - p; // not just substr because of the eventual overlap
            for (int k = 0; k < n; k++)
                output += output[match_begin + k];
        }
    }

    return output;
}