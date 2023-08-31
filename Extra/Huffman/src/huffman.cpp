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

ostream &
operator<<(ostream &os, const HuffmanCode &code) {
    for (int i = code.lengte - 1; i >= 0; i--) {
        uint a = (code.voorstelling >> i) & 0x1;
        os << a;
    }
    return os;
}

map<char, uint> maakFrequentieTabel(istream &s) {

    map<char, uint> freq;
    char c;
    while (s.get(c)) {
        freq[c]++;
    }

    freq[PSEUDO_EOF] = 1;
    return freq;
}

/**
 * Maakt een priority queue die Knoop-objecten teruggeeft volgens oplopend gewicht
 */
auto maak_priority_queue() {

    // Comparator die de gewichten van knopen met elkaar vergelijkt
    auto compare_gewicht = [](const auto &p1, const auto &p2) {
        return p1->gewicht > p2->gewicht;
    };

    return priority_queue<shared_ptr<HuffmanKnoop>,
                          vector<shared_ptr<HuffmanKnoop>>,
                          decltype(compare_gewicht)>{compare_gewicht};
}

void overloop_boom(const HuffmanKnoop *k, map<char, HuffmanCode> &codering, HuffmanCode accum = {0, 0}) {

    if (k->c.has_value()) {
        codering[k->c.value()] = accum;
    } else {
        overloop_boom(k->links.get(), codering, {accum.lengte + 1, accum.voorstelling << 1});
        overloop_boom(k->rechts.get(), codering, {accum.lengte + 1, (accum.voorstelling << 1) + 1});
    }
}

map<char, HuffmanCode> maakCoderingsTabel(const HuffmanKnoop *wortel) {
    map<char, HuffmanCode> codering;
    overloop_boom(wortel, codering);

    return codering;
}

shared_ptr<HuffmanKnoop> huffman(const map<char, uint> &freq) {

    auto queue = maak_priority_queue();

    for (const auto &[c, f] : freq) {
        queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{.c = c, .gewicht = f}));
    }

    for (int i = 0; i < freq.size() - 1; i++) {
        auto links = queue.top();
        queue.pop();
        auto rechts = queue.top();
        queue.pop();

        queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{.gewicht = links->gewicht + rechts->gewicht, .links = links, .rechts = rechts}));
    }
    return queue.top();
}

std::string codeerTekst(istream &input, const map<char, HuffmanCode> &codering) {

    obitstream output;

    char c;
    while (input.get(c)) {
        auto hc = codering.at(c);
        output.schrijfbits(hc.voorstelling, hc.lengte);
    }
    auto eof = codering.at(PSEUDO_EOF);
    output.schrijfbits(eof.voorstelling, eof.lengte);
    output.flush();
    return output.str();
}

void decodeerTekst(const std::string &input, const HuffmanKnoop *wortel, ostream &output) {
    ibitstream ibs(input);
    const HuffmanKnoop *huidige_knoop = wortel;

    char *buffer = new char[1];

    bool eof = false;
    while (!ibs.eof() && !eof) {
        if (ibs.leesbit()) {
            huidige_knoop = huidige_knoop->rechts.get();
        } else {
            huidige_knoop = huidige_knoop->links.get();
        }
        if (huidige_knoop->c.has_value()) {
            if (huidige_knoop->c.value() != PSEUDO_EOF) {

                buffer[0] = huidige_knoop->c.value();
                output.write(buffer, 1);
                huidige_knoop = wortel;
            } else {
                eof = true;
            }
        }
    }

    delete[] buffer;
}