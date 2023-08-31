#pragma once

#include <map>
#include <sstream>
#include <string>
#include <memory>
#include <optional>
#include "bitstream.h"

using std::map;
using std::istream;
using std::ostream;
using std::string;
using std::shared_ptr;
using std::optional;

typedef unsigned int uint;

/**
 * Een constante die het einde van een tekst aanduidt.
 * 
 * We hergebruiken de "End of Transmission" constante uit
 * de ASCII-tabel hiervoor. 
 */
const int PSEUDO_EOF = 0x04;


/**
 * Stelt een frequentietabel die het aantal keer dat een karakter 
 * voorkomt in een opgegeven tekst teruggeeft.
 */
map<char, uint> maakFrequentieTabel(istream &s);


struct HuffmanKnoop {
    optional<char> c;
    uint gewicht;
    shared_ptr<HuffmanKnoop> links, rechts;
};

/**
 * Berekent een Huffmanboom voor een opgegeven frequentietabel van karakters
 * 
 * @param freq een woordenboek die elk karakter afbeeldt op het aantal 
 *             keer dat het voorkomt in de tekst.
 * 
 * @returns de wortel van een Huffmanboom.
 * 
 */
shared_ptr<HuffmanKnoop> huffman(const map<char, uint> &freq);


struct HuffmanCode {
    uint lengte;
    uint voorstelling;

};

ostream &
operator<<(ostream &os, const HuffmanCode &code);

/**
 * Berekent een Huffmancodering aan de hand van een Huffmanboom
 * 
 * @param wortel De wortel van de Huffmanboom
 * 
 * @returns een woordenboek die een karakter afbeeldt op een Huffmancode
 * 
 */
map<char, HuffmanCode> maakCoderingsTabel(const HuffmanKnoop* wortel);


/**
 * Codeert de gegeven input aan de hand van de gegeven Huffmancodering.
 * 
 */
std::string codeerTekst(istream& input, const map<char, HuffmanCode>& codering);

/**
 * Decodeert de gegeven input aan de hand van de gegeven Huffmanboom, en schrijft deze weg in output
 * 
 */
void decodeerTekst(const std::string& input, const HuffmanKnoop* wortel, ostream& output);