#include <iostream>
#include <string>
#include <queue>
#include <vector>

#include "patricia.h"
#include "stringmetbits.h"


void zoeken_in_eenvoudige_boom(){
    Pboom boom;
    boom.maak_eenvoudige_boom();
    boom.schrijf(std::cout);

    std::cout << "\nzoeken van jaja:" << boom.zoek(StringMetBits("jaja")) << std::endl; // 1
    std::cout << "zoeken van alfa:" << boom.zoek(StringMetBits("alfa")) << std::endl; // 2
    std::cout << "zoeken van alff:" << boom.zoek(StringMetBits("alff")) << std::endl; // 0

}

void kleine_boom_toevoegen() {

    Pboom boom;

    std::vector<StringMetBits> list{"00001","10011","00101","10010","00011","01000","01001","01110"}; // Let er op dat 1 en 0 in bits maar op de laatste bit (7) verschillen.
    for (auto i : list){
        std::cout << "**************\nToevoegen aan de boom van: " << i << std::endl;
        boom.voegtoe(i);
    }

    boom.schrijf(std::cout);
    std::cout << "Aantal Knopen: " << boom.aantalKnopen() << std::endl;
}

void lees_bijbel(Pboom& boom) {
    // Bijbel inlezen.
    std::ifstream in;
    in.open("bible.txt");
    if (!in.good()) {
        throw "Failed to read file.";
    }
    int totaal_the = 0;
    int totaalwoorden = 0;
    while (in.good()) {
        std::string s;
        in >> s;
        if (s != "") {
            StringMetBits woord(s);
            boom.voegtoe(woord);
            if (s == "the") {
                totaal_the++;
            }
            totaalwoorden++;
        }
    }
}

void lees_test() {
    Pboom boom;
    lees_bijbel(boom);

    std::priority_queue<WordCount> prio = boom.top20();
    for (unsigned int i = prio.size(); i > 0; i--) {
        std::pair<int, StringMetBits> p = prio.top();
        std::cout << i << ". " << p.second << " - " << p.first << std::endl;
        prio.pop();
    }

}


int main() {
    zoeken_in_eenvoudige_boom();
    // kleine_boom_toevoegen();
    // lees_test();
}
