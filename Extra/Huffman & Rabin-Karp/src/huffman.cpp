#include "huffman.h"
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <vector>
using std::cout;
using std::make_shared;
using std::optional;
using std::priority_queue;
using std::shared_ptr;
using std::vector;

struct Knoop {
    Knoop(uchar c, uint f) : c(c), gewicht(f) {}
    Knoop(shared_ptr<Knoop> links, shared_ptr<Knoop> rechts, uint f) : links(links), rechts(rechts), gewicht(f) {}

    // mogelijke alternatieven  om aan te geven dat dit veld niets bevat
    // - extra boolean `isblad`,
    // - \0 gebruiken als karakter
    optional<uchar> c;
    uint gewicht;

    // gebruik hier shared_ptr<Knoop> ipv Knoop*. De shared_ptr telt immers bij hoeveel verwijzingen er zijn naar
    // het onderliggende Knoop-object. Als dit op 0 komt te staan wordt het onderliggende object verwijderd.
    shared_ptr<Knoop> links, rechts;
};

/**
 * Maakt een priority queue die Knoop-objecten teruggeeft volgens oplopend gewicht
 */
auto maak_priority_queue() {

    // Comparator die de gewichten van knopen met elkaar vergelijkt
    auto compare_gewicht = [](const auto &p1, const auto &p2) {
        return p1->gewicht > p2->gewicht;
    };

    return priority_queue<shared_ptr<Knoop>,
                          vector<shared_ptr<Knoop>>,
                          decltype(compare_gewicht)>{compare_gewicht};
}

// Hulpfuncties moeten niet header-file worden vermeld.
// Ze moeten dan wel VOOR de functie die ze gebruikt in het cpp-bestand voorkomen.
//
// Indien je de hulpfunctie na de oproepende functie wil kunnen schrijven, dan moet ze wel
// in de header-file voorkomen. Verplaats in dat geval ook de struct `Knoop` naar de header-file
void overloop_boom(shared_ptr<Knoop> k, map<uchar, string> &codering, string accum = "") {

    if (k->c.has_value()) {
        codering[k->c.value()] = accum;
    } else {
        overloop_boom(k->links, codering, accum + "0");
        overloop_boom(k->rechts, codering, accum + "1");
    }
}

map<uchar, string> huffman(const map<uchar, uint> &freq) {

    auto queue = maak_priority_queue();

    for (const auto &[c, f] : freq) {
        queue.push(make_shared<Knoop>(Knoop(c, f)));
    }

    for (int i = 0; i < freq.size() - 1; ++i) { //of while(queue.size() > 1)
        auto links = queue.top();
        queue.pop();
        auto rechts = queue.top();
        queue.pop();

        // links is altijd kleiner dan rechts, dit controleren is onnodig.
        // rechts en links omwisselen geeft een andere huffmancodering (want gespiegelde boom),
        // maar evenzeer een geldige oplossing.

        queue.push(make_shared<Knoop>(Knoop(links, rechts, links->gewicht + rechts->gewicht)));
    }

    map<uchar, string> codering;
    overloop_boom(queue.top(), codering);

    return codering;
}