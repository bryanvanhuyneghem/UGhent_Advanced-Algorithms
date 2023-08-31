#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "huffman.h"

#include <sstream>
using std::stringstream;
using std::cout;

TEST_CASE("Frequentietabel") {
    stringstream a("abracadabra");

    auto freq = maakFrequentieTabel(a);

    REQUIRE(freq['a'] == 5);
    REQUIRE(freq['b'] == 2);
    REQUIRE(freq['c'] == 1);
    REQUIRE(freq['d'] == 1);
    REQUIRE(freq['r'] == 2);
    REQUIRE(freq[PSEUDO_EOF] == 1);
    REQUIRE(freq.size() == 6);
}

TEST_CASE("Coderingstabel") {
    stringstream a("abracadabra");

    auto freq = maakFrequentieTabel(a);

    auto codering = maakCoderingsTabel(huffman(freq).get());

    for (const auto &[c, code] : codering) {
        cout << "Code '" << c << "' heeft voorstelling: " << code << "\n";
    }

    REQUIRE(codering['a'].lengte == 1);
    REQUIRE(codering['b'].lengte == 3);
    REQUIRE(codering['c'].lengte <= 4);
    REQUIRE(codering['d'].lengte <= 4);
    REQUIRE(codering['r'].lengte == 3);
    REQUIRE(codering[PSEUDO_EOF].lengte <= 4);
}

TEST_CASE("Coderen en decoderen") {
    stringstream a("abracadabra");

    auto freq = maakFrequentieTabel(a);
    auto wortel = huffman(freq);
    auto codering = maakCoderingsTabel(wortel.get());

    // ga terug naar het begin van de stream
    a.clear();
    a.seekg(0);

    string gecodeerd = codeerTekst(a,codering);
    stringstream b;
    decodeerTekst(gecodeerd, wortel.get(), b);

    //negeer eventuele extra karakters in de decodering.
    REQUIRE(a.str() == b.str().substr(0, a.str().size()));
}