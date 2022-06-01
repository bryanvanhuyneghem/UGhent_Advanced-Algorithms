#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "patricia.h"
#include <sstream>

TEST_CASE("zoek-functie", "[zoek]"){
    std::cout << "zoek test aanvullen " << std::endl;
    Pboom boom;
    boom.maak_eenvoudige_boom();
    
    StringMetBits s1("alfa");
    StringMetBits s2("beta");
    StringMetBits s3("delta");
    StringMetBits s4("jaja");
    StringMetBits s5("baby");

    REQUIRE(boom.zoek(s1) == 2);
    REQUIRE(boom.zoek(s2) == 3);
    REQUIRE(boom.zoek(s3) == 1);
    REQUIRE(boom.zoek(s4) == 1);
    REQUIRE(boom.zoek(s5) == 2);
    REQUIRE(boom.zoek(StringMetBits("Fout")) == 0);
    REQUIRE(boom.zoek(StringMetBits("NietinBoom")) == 0);
}


TEST_CASE("Voorbeeld theorie toevoegen ", "[example]"){
    Pboom boom;

    std::vector<StringMetBits> list{"00001","10011","00101","10010","00011","01000","01001","01110"};

    for (auto i : list){
        boom.voegtoe(i);
    }
    
    REQUIRE(boom.aantalKnopen() == 8);
    REQUIRE(boom.geefWortelSleutel() == "10011");
}

TEST_CASE("Voorbeeld theorie toevoegen + zoeken", "[example]"){
    Pboom boom;

    std::vector<StringMetBits> list{"00001","10011","00101","10010","00011","01000","01001","01110"};

    for (auto i : list){
        boom.voegtoe(i);
    }
    
    for (auto i : list){
        REQUIRE(boom.zoek(i));
    }
    REQUIRE_FALSE(boom.zoek("11111"));
}

TEST_CASE("Voorbeeld 2", "[example]"){
    
    Pboom boom;

    StringMetBits s1("alfa");
    StringMetBits s2("beta");
    StringMetBits s3("delta");
    StringMetBits s4("jaja");
    StringMetBits s5("baby");

    boom.voegtoe(s1);
    boom.voegtoe(s1);

    boom.voegtoe(s2);
    boom.voegtoe(s2);
    boom.voegtoe(s2);

    boom.voegtoe(s3);

    boom.voegtoe(s4);

    boom.voegtoe(s5);
    boom.voegtoe(s5);

    REQUIRE(boom.zoek(s1) == 2);
    REQUIRE(boom.zoek(s2) == 3);
    REQUIRE(boom.zoek(s3) == 1);
    REQUIRE(boom.zoek(s4) == 1);
    REQUIRE(boom.zoek(s5) == 2);

    std::ostringstream stream;
    boom.schrijf(stream);
    REQUIRE(stream.str().size() == 300);
    std::string checkstring = "Wortel van de boom: jaja\n(alfa [2,32 ] )\n  Linkerkind: alfa\n  Rechterkind: alfa\n(beta [3,6 ] )\n  Linkerkind: alfa\n  Rechterkind: baby";
    REQUIRE_FALSE(stream.str().substr(0, 133).compare(checkstring));
}