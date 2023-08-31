#include <fstream>
#include <iostream>

#include "ternaire-zoekboom.h"

void eenvoudige_test() {
    TernaireZoekboom tz;

    string woorden[] = {"dit", "dat", "diets", "diesel", "differentiaal", "die"};
    for (string woord : woorden) {
        tz.voegtoe(woord);
    }

    std::cout << "dit in woordenboek: " << tz.zoek("dit") << "\n";
    std::cout << "dik in woordenboek: " << tz.zoek("dik") << "\n";
    std::cout << "diets in woordenboek: " << tz.zoek("diets") << "\n";
    std::cout << "differentiaal in woordenboek: " << tz.zoek("differentiaal")
              << "\n";
    std::cout << "differentiaalberekening in woordenboek: "
              << tz.zoek("differentiaalberekening") << "\n";

    std::vector<string> auto_complete = tz.auto_complete("die");

    std::cout << "Woorden met prefix 'die': ";
    for (auto w : auto_complete) {
        std::cout << w << ", ";
    }
    std::cout << "\n";

    tz.teken("../eenvoudige_test.dot");
}

void wildcard_test() {
    string productcodes[] = {"RD-R9250", "FD-R9250", "BT-DN300", "EW-EC300",
                             "CS-R9200", "BR-R9270", "ST-R9270"};

    TernaireZoekboom tz_productcodes;
    for (string code : productcodes) {
        tz_productcodes.voegtoe(code);
    }

    // het opsplitsen van de tekst over 2 lijnen vermijdt warnings over trigraphs
    // cfr. https://en.wikipedia.org/wiki/Digraphs_and_trigraphs#C
    std::cout << "Productcodes die voldoen aan ??"
                 "-R92: ";
    std::vector<string> auto_complete_productcodes =
        tz_productcodes.auto_complete_wildcard(
            "??"
            "-R92");
    for (auto w : auto_complete_productcodes) {
        std::cout << w << ", ";
    }
    std::cout << "\n";

    tz_productcodes.teken("../productcodes.dot");
}

void woordenboek_test() {

    std::ifstream woordenlijst("woordenlijst.txt");
    string woord;

    TernaireZoekboom tz;

    while (std::getline(woordenlijst, woord)) {
        tz.voegtoe(woord);
    }

    string te_zoeken;

    std::cout << "Op te zoeken woord: ";
    std::cin >> te_zoeken;

    while (te_zoeken.size() > 0) {
        std::cout << "Woord in woordenlijst: " << (tz.zoek(te_zoeken) ? "ja" : "nee") << "\n";

        std::vector<string> auto_complete = tz.auto_complete(te_zoeken);

        std::cout << "Auto-complete: ";
        for (int i = 0; i < auto_complete.size() && i < 10; i++) {
            std::cout << auto_complete[i] << ", ";
        }

        if (auto_complete.size() > 10) {
            std::cout << "+ " << auto_complete.size() - 10 << " extra";
        }

        std::cout << "\n\n";

        std::cout << "Op te zoeken woord: ";
        std::cin >> te_zoeken;
    }
}

int main() {

    eenvoudige_test();

    wildcard_test();

    woordenboek_test();

    return 0;
}