#include "kerstman_prob.h"
#include <iostream>
#include <random>

using std::cout;
using std::endl;

double kerstman_prob::f(const vector<int> &s)
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

bool kerstman_prob::isOplossing(const vector<int> &deeloplossing)
{
    return deeloplossing.size() == d.size();
};

vector<pair<int, double>> kerstman_prob::geefVolgendePunt(const vector<int> &deeloplossing)
{
    
    vector<bool> bezocht(d.size(), false);
    vector<int> onbezocht;
    for(int i: deeloplossing){
        bezocht[i] = true;
    }
    for(int i = 0; i < bezocht.size(); i++){
        if(bezocht[i] == false){
            onbezocht.push_back(i);
        }
    }

    vector<pair<int, double>> mogelijke_punten;
    mogelijke_punten.reserve(onbezocht.size());
    
    const bool is_eerste = deeloplossing.size() == 0;
    for(int i : onbezocht){
        double afstand = 1.0;
        if(!is_eerste){
            const int last = deeloplossing[deeloplossing.size() - 1];
            afstand = d[last][i];
        }
        mogelijke_punten.emplace_back(std::make_pair(i, 1.0 / afstand));
    }
    return mogelijke_punten;
    
};

void kerstman_prob::pickAtRandom(vector<int> &oplossing)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, (oplossing.size() - 1));

    if(oplossing.size() < 2){
        return;
    }
    int stad1 = dis(gen);
    int stad2 = dis(gen);
    while(stad1 == stad2){
        stad2 = dis(gen);
    }
    if(stad1 > stad2){
        std::swap(stad1, stad2);
    }

    for(int i = 0; i < (stad2-stad1)/2; i++){
        std::swap(oplossing[stad1 + i], oplossing[stad2 - i]);
    }

};

void kerstman_prob::verbeterLokaal(vector<int> &oplossing)
{
    const double start_f = f(oplossing);
    vector<int> best = oplossing;
    double best_f = start_f;

    const int N = oplossing.size();
    bool stuck = false;

    auto berekenVerschil = [&best, this, N](int a, int b){
        double deltaf =  0;
        deltaf -= d[best[(a-1)%N]][best[a]];
        deltaf -= d[best[a]][best[(a+1)%N]];

        deltaf -= d[best[(b-1)%N]][best[b]];
        deltaf -= d[best[b]][best[(b+1)%N]];
        
        deltaf += d[best[(a-1)%N]][best[b]];
        deltaf += d[best[b]][best[(a+1)%N]];

        deltaf += d[best[(b-1)%N]][best[a]];
        deltaf += d[best[a]][best[(b+1)%N]];
        
        return deltaf;
    }; 

    int teller = 0;
    while(!stuck && teller < 10000){
        stuck = true;
        for(int i = 0; i < N; i++){
            for(int j = i+1; j < N; j ++){
                double deltaf = berekenVerschil(i,j);
                if(deltaf < 0){
                    stuck = false;

                    std::swap(best[i], best[j]);
                    best_f = f(best);
                }
            }
        }
        
        teller++;
    }
    next:
    std::cout << "stuck: "  << stuck << " k:" << teller << "\n" << std::endl;
    
    if(best_f < start_f){
        oplossing = std::move(best);
    }
    /*
    const double start_f = f(oplossing);
    std::cout << start_f << "\n";
    vector<int> best;
    double best_f = start_f;

    vector<int> nieuw = oplossing;
    std::cout << nieuw.size() << "\n";
    double new_f = 0;
    
    do {
        pickAtRandom(nieuw);
        new_f = f(nieuw);


        if(teller%10000 == 0)
            std::cout << new_f << "\n";

        if(new_f < best_f && nieuw.size() > 0){
            std::cout << nieuw.size() << "\n";
            best = std::move(nieuw);
            best_f = new_f;
        }
        teller++;

    } while(new_f < start_f || teller < 10000000);


    if(best_f < start_f && best.size() > 0){
        oplossing = std::move(best);
    }
    */
};