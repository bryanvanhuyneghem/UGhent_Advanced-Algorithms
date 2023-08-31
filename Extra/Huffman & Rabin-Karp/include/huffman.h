#pragma once

#include <map>
#include <string>
using std::map;
using std::string;

typedef unsigned char uchar;
typedef unsigned int uint;

/**
 * Berekent de optimale Huffmancodering voor een tekst waarin de
 * karakters voorkomen met de opgegeven frequenties.
 * 
 * @param freq een woordenboek die elk karakter afbeeldt op het aantal 
 *             keer dat het voorkomt in de tekst.
 * 
 * @returns een woordenboek die elk karakter afbeeldt op zijn optimale binaire
 *          voorstelling. We gebruiken voor het gemak een `string` hiervoor.
 * 
 */
map<uchar, string> huffman(const map<uchar, uint> &freq);