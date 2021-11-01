#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "kerstman.h"
#include "simulatedannealing.h"


#include "kerstman_sa.h"
#include "kerstman_prob.h"

TEST_CASE("Test oplossing is geldig", "[prob]")
{
    vector<int> opl = {17, 79, 27, 26, 42, 64, 100, 167, 161, 29, 31, 178, 4, 11, 134, 20, 102, 113, 122, 22, 135, 13, 175, 28, 46, 144, 18, 68, 117, 89, 36, 125, 164, 61, 149, 32, 119, 71, 12, 103, 95, 49, 101, 99, 57, 58, 123, 154, 163, 62, 172, 118, 74, 168, 140, 109, 132, 156, 171, 69, 63, 21, 7, 51, 82, 157, 77, 15, 47, 90, 120, 139, 129, 39, 56, 0, 91, 174, 152, 75, 53, 146, 5, 121, 137, 147, 50, 88, 126, 43, 155, 6, 70, 165, 59, 142, 141, 124, 159, 8, 37, 96, 143, 162, 128, 23, 166, 41, 14, 131, 106, 67, 98, 111, 2, 65, 85, 54, 148, 34, 93, 114, 38, 160, 104, 86, 115, 73, 40, 97, 78, 80, 16, 44, 60, 158, 66, 35, 10, 84, 179, 133, 138, 107, 76, 150, 170, 153, 9, 116, 1, 108, 72, 45, 92, 176, 130, 25, 55, 177, 127, 136, 52, 145, 173, 105, 94, 30, 151, 110, 87, 112, 33, 48, 24, 169, 3, 19, 83, 81};
    vector<vector<double>> afst = berekenAfstanden();
    kerstman_prob prob(afst);
    REQUIRE(prob.isOplossing(opl));
}

TEST_CASE("Test objectieffunctie oplossing correct", "[prob]")
{
    vector<int> opl = {17, 79, 27, 26, 42, 64, 100, 167, 161, 29, 31, 178, 4, 11, 134, 20, 102, 113, 122, 22, 135, 13, 175, 28, 46, 144, 18, 68, 117, 89, 36, 125, 164, 61, 149, 32, 119, 71, 12, 103, 95, 49, 101, 99, 57, 58, 123, 154, 163, 62, 172, 118, 74, 168, 140, 109, 132, 156, 171, 69, 63, 21, 7, 51, 82, 157, 77, 15, 47, 90, 120, 139, 129, 39, 56, 0, 91, 174, 152, 75, 53, 146, 5, 121, 137, 147, 50, 88, 126, 43, 155, 6, 70, 165, 59, 142, 141, 124, 159, 8, 37, 96, 143, 162, 128, 23, 166, 41, 14, 131, 106, 67, 98, 111, 2, 65, 85, 54, 148, 34, 93, 114, 38, 160, 104, 86, 115, 73, 40, 97, 78, 80, 16, 44, 60, 158, 66, 35, 10, 84, 179, 133, 138, 107, 76, 150, 170, 153, 9, 116, 1, 108, 72, 45, 92, 176, 130, 25, 55, 177, 127, 136, 52, 145, 173, 105, 94, 30, 151, 110, 87, 112, 33, 48, 24, 169, 3, 19, 83, 81};
    vector<vector<double>> afst = berekenAfstanden();
    kerstman_prob prob(afst);
    REQUIRE((int)prob.f(opl) == 4952);
}

TEST_CASE("Test oplossing geldig", "[prob]")
{
    vector<vector<double>> afst = berekenAfstanden();
    kerstman_prob prob(afst);
    vector<int> opl = prob.geefOptimum(500);
    REQUIRE(prob.isOplossing(opl));
}

TEST_CASE("Test oplossing verbeter lokaal", "[prob]")
{
    vector<vector<double>> afst = berekenAfstanden();
    kerstman_prob prob(afst);
    vector<int> opl = prob.geefOptimum(500);
    prob.verbeterLokaal(opl);
    REQUIRE(opl.size() > 0);
    REQUIRE(prob.f(opl) < 750);
}

TEST_CASE("Test simulated annealing", "[sa]")
{
    vector<vector<double>> afst = berekenAfstanden();
    kerstman_sa annealing(afst);
    kerstman_prob prob(afst);
    vector<int> annealingOplossing = annealing.oplossing();
    REQUIRE(prob.isOplossing(annealingOplossing));
    REQUIRE(annealing.f(annealingOplossing) < 625.0);
}