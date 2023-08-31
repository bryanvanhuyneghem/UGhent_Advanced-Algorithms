#include "ternaire-zoekboom.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>


TernaireZoekboom::TernaireZoekboom(){}


void TernaireZoekboom::voegtoe(string woord){

    std::unique_ptr<TZKnoop>* vorige_knoop;
    std::unique_ptr<TZKnoop>* huidige_knoop = &wortel;

    for(char c : woord){
        std::unique_ptr<TZKnoop>* volgende_knoop = nullptr;

        bool gevonden = false;
        while(!gevonden){

            if(*huidige_knoop == nullptr){
                TZKnoop k;

                (*huidige_knoop) = std::make_unique<TZKnoop>();
                (*huidige_knoop)->c = c;

                gevonden = true;
                
            }else{

                if((*huidige_knoop)->c == c){
                    gevonden = true;
                }else if((*huidige_knoop)->c > c){
                    huidige_knoop = &((*huidige_knoop)->kleiner);
                }else{
                    huidige_knoop = &((*huidige_knoop)->groter);
                }
            }
        }
        vorige_knoop = huidige_knoop;
        huidige_knoop = &((*huidige_knoop)->gelijk); //naar volgende karakter;
    }

    //de 'vorige_knoop' pointer bevat de knoop met de laatste letter van het woord
    if((*vorige_knoop)->in_boom){
        throw std::runtime_error("sleutel bestaat al");
    }
    (*vorige_knoop)->in_boom = true;

}


bool TernaireZoekboom::zoek_woord(TZKnoop* knoop, string woord, int pos){
    char c = woord[pos];

    while(knoop != nullptr){
        if(knoop-> c == c){
            if(pos == woord.size() -1){
                return knoop->in_boom;
            }else{
                return zoek_woord(knoop->gelijk.get(), woord, pos+1);
            }
        }else if(c < knoop->c){
            knoop = knoop->kleiner.get();
        }else{
            knoop = knoop->groter.get();
        }
    }

     return false;
}

bool TernaireZoekboom::zoek(string woord){
    return zoek_woord(wortel.get(), woord, 0);
}

std::vector<string> TernaireZoekboom::auto_complete(string prefix){

    std::vector<string> resultaten;
    auto_complete_rec(prefix, wortel.get(), "", resultaten);

    return resultaten;
}

void TernaireZoekboom::auto_complete_rec(string prefix, TZKnoop* knoop, string woord, std::vector<string>& resultaten){

    if(knoop == nullptr){
        return;
    }

    if(prefix.size() > 0){
        //we zoeken het eerstvolgende karakter uit de resterende 
        char c = prefix[0];
        if (knoop->c == c){
            if(prefix.size() == 1){
                // we hebben de volledige prefix gevonden. Voeg deze toe aan resultaten indien ze ook in boom zit.

                if(knoop->in_boom){
                    resultaten.push_back(woord + knoop->c);
                }
            }

            auto_complete_rec(prefix.substr(1, prefix.size()), knoop->gelijk.get(), woord + c, resultaten);
        }
        else if(c < knoop->c){
            auto_complete_rec(prefix, knoop->kleiner.get(), woord, resultaten);
        }else{
            auto_complete_rec(prefix, knoop->groter.get(), woord, resultaten);
        }

    }else {
        // de prefix werd al gevonden.
        // we overlopen nu alle knopen volgens DEZ om ze alfabetisch te kunnen teruggeven

        auto_complete_rec(prefix, knoop->kleiner.get(), woord, resultaten);

        if(knoop->in_boom){
            resultaten.push_back(woord + knoop->c);
        }

        auto_complete_rec(prefix, knoop->gelijk.get(), woord + knoop->c, resultaten);
        auto_complete_rec(prefix, knoop->groter.get(), woord, resultaten);
    }
    
}


std::vector<string> TernaireZoekboom::auto_complete_wildcard(string prefix){

    std::vector<string> resultaten;
    auto_complete_wildcard_rec(prefix, wortel.get(), "", resultaten);

    return resultaten;
}

void TernaireZoekboom::auto_complete_wildcard_rec(string prefix, TZKnoop* knoop, string woord, std::vector<string>& resultaten){

    if(knoop == nullptr){
        return;
    }

    if(prefix.size() > 0){
        //we zoeken het eerstvolgende karakter uit de resterende 
        char c = prefix[0];
        if(c == '?'){
            auto_complete_wildcard_rec(prefix, knoop->kleiner.get(), woord, resultaten);
            auto_complete_wildcard_rec(prefix.substr(1, prefix.size()), knoop->gelijk.get(), woord + knoop->c, resultaten);
            auto_complete_wildcard_rec(prefix, knoop->groter.get(), woord, resultaten);

        }else if (knoop->c == c){
            if(prefix.size() == 1){
                // we hebben de volledige prefix gevonden. Voeg deze toe aan resultaten indien ze ook in boom zit.

                if(knoop->in_boom){
                    resultaten.push_back(woord + knoop->c);
                }
            }

            auto_complete_wildcard_rec(prefix.substr(1, prefix.size()), knoop->gelijk.get(), woord + c, resultaten);
        }
        else if(c < knoop->c){
            auto_complete_wildcard_rec(prefix, knoop->kleiner.get(), woord, resultaten);
        }else{
            auto_complete_wildcard_rec(prefix, knoop->groter.get(), woord, resultaten);
        }

    }else {
        // de prefix werd al gevonden.
        // we overlopen nu alle knopen volgens DEZ om ze alfabetisch te kunnen teruggeven

        auto_complete_wildcard_rec(prefix, knoop->kleiner.get(), woord, resultaten);

        if(knoop->in_boom){
            resultaten.push_back(woord + knoop->c);
        }

        auto_complete_wildcard_rec(prefix, knoop->gelijk.get(), woord + knoop->c, resultaten);
        auto_complete_wildcard_rec(prefix, knoop->groter.get(), woord, resultaten);
    }
}

std::string TZKnoop::tekenKnoop(std::ostream& uit, int& knoopteller){
    std::ostringstream wortelstring;
    wortelstring << '"' << this->c << ++knoopteller << '"';
    uit << wortelstring.str() << "[label=\"" << this->c << "\"]";
    if (this->in_boom){
        uit << "[color=red]";
    }
    uit << ";\n";

    string kleinerkind;
    string gelijkkind = "";
    string groterkind = "";
    if(this->kleiner){
        kleinerkind = this->kleiner->tekenKnoop(uit, knoopteller);
    }
    else{
        std::stringstream tel;
        tel << ++knoopteller;
        kleinerkind = "\"null"  + tel.str() + '"';
        uit << kleinerkind << " [shape=point];\n";
    }
    if(this->gelijk){
        gelijkkind = this->gelijk->tekenKnoop(uit, knoopteller);
    }
    else{
        std::stringstream tel;
        tel << ++knoopteller;
        gelijkkind = "\"null"  + tel.str() + '"';
        uit << gelijkkind << " [shape=point];\n";
    }

    if(this->groter){
        groterkind = this->groter->tekenKnoop(uit, knoopteller);
    }
    else{
        std::stringstream tel;
        tel << ++knoopteller;
        groterkind = "\"null"  + tel.str() + '"';
        uit << groterkind << " [shape=point];\n";
    }

    uit << wortelstring.str() << " -> " << kleinerkind << ";\n";
    uit << wortelstring.str() << " -> " << gelijkkind << ";\n";
    uit << wortelstring.str() << " -> " << groterkind << ";\n";
    
    // };
    return wortelstring.str();
}

void TernaireZoekboom::teken(const char* bestandsnaam) const{
    std::ofstream uit(bestandsnaam);
    uit << "digraph {\n";
    int knoopteller = 0;
    this->wortel->tekenKnoop(uit, knoopteller);
    uit << "}";
}