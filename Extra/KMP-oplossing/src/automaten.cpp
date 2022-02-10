#include "automaten.h"


#define ALFABET_SIZE 128


DA::DA(const std::string patroon):toestanden(patroon.size()+1)
{
    this->patroon = patroon;
    std::vector<int> x(ALFABET_SIZE, 0);

    vector<vector<int>> tabel;
    int x_col = x_col;
    for(int k = 0; k<patroon.size() ; k++){
        uchar c = patroon[k];
        tabel.push_back(x);

        tabel[k][c] = k+1;

        // set new x kolom
        x = tabel[x[c]];
    }
    
    for (int i = 0; i < tabel.size(); i++)
    {
        for(int c =0; c < ALFABET_SIZE; c++){
            toestanden[i].overgangen[c] = tabel[i][c];
        }
    }  
    // een eindknoop toevoegen na de hele sequentie
    toestanden[toestanden.size() - 1].eindToestand = true;
}

bool DA::zitInTweet(const string &s, int& vergelijkingen)
{
    DAToestand *huidigeToestand = &toestanden[0]; // 0 bevat altijd de starttoestand
    int teller = s.size()-1;
    for (uchar c : s)
    {
        if(huidigeToestand->eindToestand){ // eindtoestand bereikt == string gevonden
            return true;
        }
        if(patroon.size() > teller && huidigeToestand->overgangen[c] < patroon.size() - teller){ //Als er niet genoeg karakters in de string overblijven om de hele automaat te kunnen doorlopen.
            return false;
        }
        huidigeToestand = &toestanden[huidigeToestand->overgangen[c]];
        vergelijkingen++;
        teller--;
    }

    return huidigeToestand->eindToestand;
}

ostream & operator<<(ostream& os, const DA & da)
{

    os << "digraph {\n";
    os << "\t rankdir=\"LR\";\n" ;

    for(int i = 0; i < da.toestanden.size(); i++){
        const DA::DAToestand *dat = &da.toestanden[i];

        if(dat->eindToestand){
            os << "\t " << i << " [shape=square];\n";
        }
        for(auto [karakter, buur_nr] : dat->overgangen){
            os << "\t " << i << " -> " << buur_nr << " [label=\"";
            if(karakter != epsilon){
                os << karakter;
            }else {
                os << "ε";
            } 
            os << "\"];\n";
        }
    }

    os << "}\n";

    return os;
}
