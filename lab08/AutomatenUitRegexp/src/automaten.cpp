#include "automaten.h"
#include <stack>
DA::DA(const Regexp & regexp){
    NA na(regexp);
    convertNAToDA(na);
}

void DA::convertNAToDA(const NA& na){
    
    // 1. Bijhouden wat al de mogelijke invoersymbolen zijn
    
    int tekens = 0;
    for(auto&& overgang : na.overgangen){
        if(overgang.symbol != na.EPSILON){
            auto place = symbols.find(overgang.symbol);
            if(place == symbols.end()){
                symbols.emplace_hint(place, overgang.symbol, tekens++);
                // of symbols[overgang.symbol] = tekens++
            }
        }
    }

    // 2. Deelverzamelingenconstructie, cursus 11.2
    std::map<std::set<int>, int> volgnummer; // volgnummers DA-staten
    std::stack<std::set<int>> DEZstack; // DA-toestanden met nog te bepalen overgangen

    std::set<int> T = {0}; // begintoestand van DA
    epsilonSluiting(na, T);
    int staatNummer = 0;
    volgnummer[T] = staatNummer++;
    overgangstabel.emplace_back(std::vector<int>(tekens, -1));
    DEZstack.push(T);

    while(!DEZstack.empty()){
        T = DEZstack.top();
        DEZstack.pop();

        for(const auto& [symbol, tekenID]: symbols){
            std::set<int> nieuweToestand = bereikbaarViaSymbolUitOudeStaat(na, T, symbol);
            epsilonSluiting(na, nieuweToestand);
            
            if(volgnummer.find(nieuweToestand) == volgnummer.end()){
                volgnummer[nieuweToestand] = staatNummer++;
                DEZstack.push(nieuweToestand);
            }
            
            // Updaten van de overgangstabel van de DA
            // ----------------------------------------
            const int huidige_volgnummer = volgnummer[T];
            const int nieuw_volgnummer = volgnummer[nieuweToestand];
            
            // Indien de tabel nog niet groot genoeg is, breid hem uit
            if(overgangstabel.size() <= nieuw_volgnummer){
                overgangstabel.emplace_back(std::vector<int>(tekens, -1));
                
            }

            overgangstabel[huidige_volgnummer][tekenID] = nieuw_volgnummer;
            // ----------------------------------------
        }
    }
    
    for(const auto& [set, nr]: volgnummer){
        for(int to: set){
            if(to == na.aantalStatenbits - 1){
                terminaleStaten.insert(nr); 
            }
        }
    }
}

// cursus 11.1
void DA::epsilonSluiting(const NA& na, std::set<int>& staat){
    for(int statenbit: staat){
        bereikbaarViaSymbolRec(na, staat, statenbit, na.EPSILON); // analoog aan cursus: while(!stack.ledig()); recursief doordoen
    }
}

void DA::bereikbaarViaSymbolRec(const NA& na, std::set<int>& staat, int from, char symbol){
    for(auto& trans: na.overgangen){
        if(trans.from == from && trans.symbol == symbol){
            staat.insert(trans.to);
            bereikbaarViaSymbolRec(na, staat, trans.to, symbol);
        }
    }
}

std::set<int> DA::bereikbaarViaSymbolUitOudeStaat(const NA& na, std::set<int>& oude_staat, char symbol){
    std::set<int> nieuwe_staat;
    for(int statenbit: oude_staat){
        bereikbaarViaSymbolRec(na, nieuwe_staat, statenbit, symbol);
    }
    return nieuwe_staat;
}

bool DA::zitInTaal(const string& s){
    int state = 0;
    for(char c: s){
        state = overgangstabel[state][symbols[c]];
        if(state ==  -1){
            return false;
        }
    }
    return terminaleStaten.find(state) != terminaleStaten.end();

}