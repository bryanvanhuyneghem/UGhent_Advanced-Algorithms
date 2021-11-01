#include "kerstman_sa.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
using std::cout;
using std::endl;

std::vector<int> kerstman_sa::beginOplossing()
{
    std::vector<int> opl(d.size());
    std::iota(std::begin(opl), std::end(opl), 0);
    std::random_shuffle(std::begin(opl), std::end(opl));

    return opl;
};

std::pair<std::vector<int>,double> kerstman_sa::neemRandom(const std::vector<int> &s)
{

    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, (s.size() - 1));

    std::vector<int> nieuw = s;
    //return nieuw;

    if(nieuw.size() < 2){
        return {nieuw, 0.0};
    }
    
    int stad1 = dis(gen);
    int stad2 = dis(gen);

    while(stad1 == stad2){
        stad2 = dis(gen);
    }
    if(stad1 > stad2){
        std::swap(stad1, stad2);
    }
    const int n = s.size();

    double deltaf = -(d[s[(stad1-1)%n]][s[stad1]] + d[s[stad2]][s[(stad2+1)%n]]);

    for(int i = 0; i < (stad2-stad1)/2; i++){
        std::swap(nieuw[stad1 + i], nieuw[stad2 - i]);
    }
    deltaf += d[nieuw[(stad1-1)%n]][nieuw[stad1]];
    deltaf += d[nieuw[stad2]][nieuw[(stad2+1)%n]];
    
    return {nieuw, deltaf};
};

double kerstman_sa::f(const std::vector<int> &s)
{
    if(s.size() < 2){
        return 0;
    }
    
    double afstand = 0;
    for(int i = 0; i < s.size()-1; i++){
        afstand += d[s[i]][s[i+1]];
    }
    // terug naar eerste punt gaan
    afstand += d[s[s.size()-1]][s[0]];
    return afstand;
};

double kerstman_sa::p(double T, double deltaf)
{
    
    //overbodig wordt al op gecheckt
    /*if(deltaf < 0) 
        return 1.0;
    */
    return std::exp(-deltaf / T);
};

void kerstman_sa::updateT(int k)
{
    if(T < 5) {
        T *= 0.999999;
    }
    else {
        T *= 0.999999995;
    }
};

bool kerstman_sa::stopConditie() // true als simulated annealing moet stoppen
{
    return T < 0.001;
};

double kerstman_sa::beginTemperatuur()
{
    return 100;//'000'000'000;
};