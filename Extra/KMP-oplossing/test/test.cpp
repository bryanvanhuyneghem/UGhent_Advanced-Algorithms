#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "automaten.h"
#include "naiefZoeken.h"
#include <iostream>
using std::cout;

TEST_CASE("Eenvoudig patroon", "[kmp]"){
	DA automaat("AAB");
    int v = 0;
	CHECK(automaat.zitInTweet("AAB", v));
	CHECK(automaat.zitInTweet("ABAACAAB", v));
    CHECK(automaat.zitInTweet("ABAACAABA", v));
    CHECK(!automaat.zitInTweet("ABAACABAB", v));
}

TEST_CASE("Vergelijkingen", "[kmp]"){
	DA automaat("AAB");
    int v = 0;
	automaat.zitInTweet("AAB", v);
	automaat.zitInTweet("ABAACAAB", v);
    automaat.zitInTweet("ABAACAABA", v);
    automaat.zitInTweet("ABAACABAB", v);
    CHECK(v==25);
}

TEST_CASE("Naive methode zoeken", "[kmp]"){
	std::string patroon = "AAB";
    int v = 0;
	CHECK(naiefZoeken("AAB",patroon, v));
	CHECK(naiefZoeken("ABAACAAB",patroon, v));
    CHECK(naiefZoeken("ABAACAABA",patroon, v));
    CHECK(!naiefZoeken("ABAACABAB",patroon, v));
}

TEST_CASE("Naive methode vergelijkingen", "[kmp]"){
	std::string patroon = "AAB";
    int v = 0;
	naiefZoeken("AAB",patroon, v);
	naiefZoeken("ABAACAAB",patroon, v);
    naiefZoeken("ABAACAABA",patroon, v);
    naiefZoeken("ABAACABAB",patroon, v);
    CHECK(v==39);
}
