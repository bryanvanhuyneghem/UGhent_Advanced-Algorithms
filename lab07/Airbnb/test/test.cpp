#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "airbnb.h"
#include "bknoop.h"
#include <string.h>
#include <sstream>

TEST_CASE("BTree toevoegen (enkel in wortel)", "[toevoegen]")
{
    std::cout << "Test 1" << std::endl;
    Schijf<BKnoop<int, int, 5>> schijf;
    BTree<int, int, 5> boom(schijf);

    int punten[5] = {1, 6, 11, 16, 21}; 
    for (auto i : punten)
    {
        boom.voegtoe(i, 10);
    }
    // boom.schrijf(std::cout);

    REQUIRE(boom.aantalsleutelswortel() == 5);
    REQUIRE(boom.geefsleutelwortel(0) == 1);
    REQUIRE(boom.geefsleutelwortel(2) == 11);
    REQUIRE(boom.geefsleutelwortel(4) == 21);
    std::ostringstream stream;
    boom.schrijf(stream);
    REQUIRE(stream.str().size() == 98);
    REQUIRE(0 == stream.str().compare("index op schijf van knoop: 1\n --- 5 sleutels\n1 (10) 6 (10) 11 (10) 16 (10) 21 (10) \nknoop is blad\n"));
}

TEST_CASE("BTree toevoegen (wortel splitsen) met 6 sleutels", "[toevoegen]")
{
    std::cout << "Test 2" << std::endl;
    Schijf<BKnoop<int, int, 5>> schijf;
    BTree<int, int, 5> boom(schijf);

    int punten[6] = {1, 6, 11, 16, 21, 2};
    for (auto i : punten)
    {
        boom.voegtoe(i, 10);
    }
    
    REQUIRE(boom.aantalsleutelswortel() == 1);
    REQUIRE(boom.geefsleutelwortel(0) == 6);

    std::ostringstream stream;
    boom.schrijf(stream);
    REQUIRE(stream.str().size() == 234);
    REQUIRE(0 == stream.str().compare("index op schijf van knoop: 3\n --- 1 sleutels\n6 (10) \nwijzers naar:\n1 - 2 - \nindex op schijf van knoop: 2\n --- 3 sleutels\n11 (10) 16 (10) 21 (10) \nknoop is blad\nindex op schijf van knoop: 1\n --- 2 sleutels\n1 (10) 2 (10) \nknoop is blad\n"));
}

TEST_CASE("BTree van 25 sleutels", "[toevoegen]")
{
    std::cout << "Test 3 boom van 25 sleutels" << std::endl;
    Schijf<BKnoop<int, int, 5>> schijf;
    BTree<int, int, 5> boom(schijf);

    int punten[25] = {1, 6, 11, 16, 21, 2, 7, 12, 17, 22, 3, 8, 13, 18, 23, 4, 9, 14, 19, 24, 5, 10, 15, 20, 25};
    for (auto i : punten)
    {
        std::cout <<"------------------------"<<std::endl;

        boom.schrijf(std::cout);
        std::cout << i << "toegevoegd"<<std::endl;
        boom.voegtoe(i, 2 * i);
    }
    std::cout <<"+++++++++++++++++++++"<<std::endl;
    boom.schrijf(std::cout);
    REQUIRE(boom.aantalsleutelswortel() == 4);

    std::ostringstream stream;
    boom.schrijf(stream);
    REQUIRE(stream.str().size() == 568);
    std::string checkstring = "index op schijf van knoop: 3\n --- 4 sleutels\n6 (12) 12 (24) 17 (34) 21 (42) \nwijzers naar:\n1 - 2 - 4 - 5 - 6 - ";
    REQUIRE_FALSE(stream.str().substr(0, 111).compare(checkstring));
}

TEST_CASE("Zoeken in BTree", "[zoeken]")
{
    std::cout << "Test 4 zoek" << std::endl;
    Schijf<BKnoop<int, int, 5>> schijf;
    BTree<int, int, 5> boom(schijf);

    int punten[25] = {1, 6, 11, 16, 21, 2, 7, 12, 17, 22, 3, 8, 13, 18, 23, 4, 9, 14, 19, 24, 5, 10, 15, 20, 25};
    for (auto i : punten)
    {
        boom.voegtoe(i, 2 * i);
    }
    REQUIRE(boom.aantalsleutelswortel() == 4);
    REQUIRE(boom.zoekSleutel(16));
    REQUIRE(boom.zoekSleutel(8));
    REQUIRE_FALSE(boom.zoekSleutel(212));
}
