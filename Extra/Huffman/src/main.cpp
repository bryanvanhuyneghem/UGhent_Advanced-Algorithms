#include "huffman.h"

#include <iostream>
#include <fstream>
using std::ifstream;
using std::ofstream;

using std::cout;
using std::string;

int main() {
    ifstream input("hamlet.txt");

    map<char, uint> freq = maakFrequentieTabel(input);

    for (const auto &[c, f] : freq) {
        cout << "Karakter '" << c << "' komt " << f << " keer voor.\n";
    }

    shared_ptr<HuffmanKnoop> wortel = huffman(freq);
    map<char, HuffmanCode> codering = maakCoderingsTabel(wortel.get());

    for (const auto &[c, code] : codering) {
        cout << "Code '" << c << "' heeft voorstelling: " << code << "\n";
    }

    // ga terug naar het het begin van het bestand
    input.clear();
    input.seekg(0);

    string gecodeerd = codeerTekst(input, codering);
 
    ofstream output("hamlet-gedecodeerd.txt");
    decodeerTekst(gecodeerd, wortel.get(), output);

    cout << "De gedecodeerde tekst werd opgeslagen in 'hamlet-gedecodeerd.txt'\n";

    return 0;
}
