#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "automaten.h"
#include <iostream>
using std::cout;

TEST_CASE("Voorbeeld cursus", "[regexp]"){
	Regexp r("(a|b)*a(a|b)");
	DA da(r);

	CHECK(da.zitInTaal("aab"));
	CHECK(!da.zitInTaal("abb"));
	CHECK(da.zitInTaal("aaab"));
	CHECK(da.zitInTaal("aaaa"));
	CHECK(da.zitInTaal("abaab"));
	CHECK(!da.zitInTaal("ababa"));
	CHECK(!da.zitInTaal("ababb"));
}


TEST_CASE("Concatenatie", "[regexp]"){
	Regexp r("ab");
	DA da(r);

	CHECK(!da.zitInTaal("a"));
	CHECK(!da.zitInTaal("b"));
	CHECK(!da.zitInTaal("aa"));
	CHECK(da.zitInTaal("ab"));
	CHECK(!da.zitInTaal("aba"));
	CHECK(!da.zitInTaal("abb"));
	CHECK(!da.zitInTaal("abc"));
}

TEST_CASE("Of", "[regexp]"){
	Regexp r("a|b");
	DA da(r);

	CHECK(da.zitInTaal("a"));
	CHECK(da.zitInTaal("b"));
	CHECK(!da.zitInTaal("aa"));
	CHECK(!da.zitInTaal("ab"));
	CHECK(!da.zitInTaal("aba"));
	CHECK(!da.zitInTaal("abb"));
	CHECK(!da.zitInTaal("abc"));
}

TEST_CASE("Herhaling", "[regexp]"){
	Regexp r("(ab)*");
	DA da(r);

	CHECK(!da.zitInTaal("a"));
	CHECK(!da.zitInTaal("b"));
	CHECK(!da.zitInTaal("aa"));
	CHECK(da.zitInTaal("ab"));
	CHECK(!da.zitInTaal("aba"));
	CHECK(!da.zitInTaal("abb"));
	CHECK(!da.zitInTaal("abc"));
	CHECK(!da.zitInTaal("abaa"));
	CHECK(da.zitInTaal("abab"));
	CHECK(!da.zitInTaal("abababababa"));
	CHECK(da.zitInTaal("abababababab"));

}


TEST_CASE("Alfabet van vier", "[regexp]"){
	Regexp r("(a|b|c)*d(b|c)");
	DA da(r);
	CHECK(da.zitInTaal("abcdb"));
	CHECK(da.zitInTaal("abcdc"));
	CHECK(da.zitInTaal("dc"));
	CHECK(da.zitInTaal("bbbbbbbdc"));

	CHECK(!da.zitInTaal("aab"));
	CHECK(!da.zitInTaal("abb"));
	CHECK(!da.zitInTaal("aaab"));
	CHECK(!da.zitInTaal("aaaa"));
	CHECK(!da.zitInTaal("abaab"));
	CHECK(!da.zitInTaal("ababa"));
	CHECK(!da.zitInTaal("ababb"));
}