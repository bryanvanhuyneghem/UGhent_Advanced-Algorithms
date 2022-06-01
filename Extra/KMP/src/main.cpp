#include "automaten.h"
#include "naiefZoeken.h"
#include <iostream>
#include "csv.hpp"



vector<std::string> leesTweets(){
    vector<std::string> tweets;
    csv::CSVReader tweets_in("realdonaldtrump.csv");

    for (auto &row : tweets_in)
    {
        tweets.push_back(row["content"].get<std::string>());
    }
    return tweets;
}



int main(){
    std::string patroon = "AAB";
    DA automaat(patroon);
    int vergelijkingen = 0;
    int vergelijkingenNaief = 0;
   
    std::cout << "Zoeken in AAB:        " << automaat.zitInTweet("AAB", vergelijkingen) << " " << naiefZoeken("AAB", patroon, vergelijkingenNaief) << std::endl;
    std::cout << "Zoeken in ABAACAAB:   " <<  automaat.zitInTweet("ABAACAAB", vergelijkingen)  << " " << naiefZoeken("ABAACAAB", patroon, vergelijkingenNaief) << std::endl;
    std::cout << "Zoeken in ABAACAABA:  " <<  automaat.zitInTweet("ABAACAABA", vergelijkingen) << " " << naiefZoeken("ABAACAABA", patroon, vergelijkingenNaief) << std::endl;
    std::cout << "Zoeken in ABAACABAB:  " <<  automaat.zitInTweet("ABAACABAB", vergelijkingen) << " " << naiefZoeken("ABAACABAB", patroon, vergelijkingenNaief) << std::endl;
    std::cout << "Naief: " << vergelijkingenNaief << " kmp: " << vergelijkingen << " vergelijkingen" << std::endl;

    patroon = "ABABAC";
    vergelijkingen = 0;
    vergelijkingenNaief = 0;
    DA automaat2(patroon);
    std::cout << "Zoeken in AABACAABABACAA:  "  << automaat2.zitInTweet("AABACAABABACAA", vergelijkingen) << " "<< naiefZoeken("AABACAABABACAA", patroon, vergelijkingenNaief) <<std::endl;
    std::cout << "Zoeken in AABACAABABBACAA: "  << automaat2.zitInTweet("AABACAABABBACAA", vergelijkingen) << " "<< naiefZoeken("AABACAABABBACAA", patroon, vergelijkingenNaief) <<std::endl;
    std::cout << "Naief: " << vergelijkingenNaief << " kmp: " << vergelijkingen << " vergelijkingen" <<  std::endl;

    std::string zoekterm = "hahaha";
    DA zoektermDA(zoekterm);
    int teller = 0;
    vergelijkingen = 0;
    vergelijkingenNaief = 0;

    vector<std::string> tweets = leesTweets();
    for(std::string tw : tweets){
        bool res1 = zoektermDA.zitInTweet(tw, vergelijkingen);
        bool res2 = naiefZoeken(tw, zoekterm, vergelijkingenNaief); 
        if(res1 && res2){
            std::cout << tw << std::endl;
            teller++;
        }
        else if(res1 || res2){
            std::cout << "ERROR: " << zoektermDA.zitInTweet(tw, vergelijkingen) <<" " <<  naiefZoeken(tw, zoekterm, vergelijkingenNaief) <<  "    " << tw <<std::endl;
        }
        
    }
    std::cout << "De zoekterm komt in " << teller << " tweets voor" << std::endl;
    std::cout << vergelijkingen << "  - Totaal aantal kmp karaktervergelijkingen in de tweets" << std::endl;
    std::cout << vergelijkingenNaief << "  - Totaal aantal naieve karaktervergelijkingen in de tweets" << std::endl;
    return 0;
}