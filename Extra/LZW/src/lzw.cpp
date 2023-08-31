#include "lzw.h"

#include <string>
#include <sstream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <tuple>
#include <iostream>
#include "bitstream.h"
#include "unordered_map"

constexpr int DATABITS = 7;
constexpr int NUMBITS = 12;
constexpr int MAX_TABLESIZE = 1 << NUMBITS;
constexpr int EOF_CODE = 1 << DATABITS;

using std::move;
using std::string;
using std::stringstream;

void initialiseer_encodeer_tabel(std::unordered_map<string, int> &tabel)
{

    for (int i = 0; i < (1 << DATABITS); i++)
    {
        string s;
        s += char(i);
        tabel[s] = i;
    }
}

std::string compress_lzw(const std::string &input)
{

    std::unordered_map<string, int> tabel;
    initialiseer_encodeer_tabel(tabel);
    int volgende_code = EOF_CODE + 1;

    string vorige, huidig;
    obitstream out;

    for (char c : input)
    {
        vorige = huidig;
        huidig += c;

        if (tabel.find(huidig) == tabel.end())
        {
            // vorige was de laatste prefix die nog voorkwam in onze tabel
            out.schrijfbits(tabel[vorige], NUMBITS);
            tabel[huidig] = volgende_code++;

            if (volgende_code == MAX_TABLESIZE)
            {
                // we hebben een overflow in de tabel
                tabel.clear();
                initialiseer_encodeer_tabel(tabel);
                volgende_code = EOF_CODE + 1;
            }

            huidig = "";
            huidig += c;
        }
    }
    out.schrijfbits(tabel[huidig], NUMBITS);
    out.schrijfbits(EOF_CODE, NUMBITS);

    out.flush();
    return out.str();
}

std::string decompress_lzw(const std::string &input)
{

    ibitstream ibs(input);
    stringstream output;

    std::vector<string> tabel(MAX_TABLESIZE);
    int volgende_code = EOF_CODE + 1;
    for (int i = 0; i < (1 << DATABITS); i++)
    {
        tabel[i] = char(i);
    }

    int x = ibs.leesbits(NUMBITS);
    if (x == EOF_CODE)
    {
        return "";
    }
    string out = tabel[x];
    string s;
    char c;

    bool eof = false;

    while (!ibs.eof() && !eof)
    {
        output << out;

        x = ibs.leesbits(NUMBITS);
        if (x == EOF_CODE)
        {
            eof = true;
            continue;
        }
        else if (x >= volgende_code) // KwKwKw-probleem
        {
            s = out + out[0];
            tabel[volgende_code++] = s;
        }
        else
        {
            s = tabel[x];
            c = s[0];
            tabel[volgende_code++] = out + c;
        }

        if (volgende_code == MAX_TABLESIZE)
        {
            // tabel zit te vol, terug resetten naar begintoestand
            volgende_code = EOF_CODE + 1;
        }

        out = move(s);
    }

    return output.str();
}