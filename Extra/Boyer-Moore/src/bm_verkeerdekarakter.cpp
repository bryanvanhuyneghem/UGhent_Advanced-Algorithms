#include "boyermoore.h"

BMVerkeerdeKarakter::BMVerkeerdeKarakter(const string &naald) :naald(naald){

    for(auto& k : verkeerdeKarakter){
        k = -1;
    }

    for(int i = 0; i  < naald.size();i++){
        verkeerdeKarakter[naald[i]] = i;
    }
}

std::queue<int> BMVerkeerdeKarakter::zoek(const string &hooiberg)
{
    laatsteAantalKaraktervergelijkingen = 0;
    std::queue<int> locaties;

    int naaldBeginPos = 0;

    while( naaldBeginPos + naald.size() <= hooiberg.size()){
        int i = naald.size() - 1; // i geeft de positie in de naald aan die we de volgende keer moeten vergelijken

        while(i >= 0 && hooiberg[naaldBeginPos + i] == naald[i]){
            laatsteAantalKaraktervergelijkingen++;
            i--;
        }

        if(i >= 0){
            laatsteAantalKaraktervergelijkingen++;
        }

        if(i < 0){
            locaties.push(naaldBeginPos);
            naaldBeginPos++; //verbeteren
        }else{
            //het is misgelopen op positie naaldBeginPos+i in de hooiberg
            int laatstePosVerkeerdKarakter = verkeerdeKarakter[hooiberg[naaldBeginPos+i]];
            if( laatstePosVerkeerdKarakter == -1){
                //karakter komt niet voor in naald, we kunnen dus de naald voorbij de fout-positie schuiven
                naaldBeginPos += i+1;
            }else if(laatstePosVerkeerdKarakter < i){
                //we verplaatsen de naald nu zodanig dat de laatste positie voor het karakter 
                // op hooiberg[naaldBeginPos+i] komt te staan

                naaldBeginPos += i-laatstePosVerkeerdKarakter;
            }else {
                // we mogen niet opschuiven in de verkeerde richting. we kiezen een veilige 1 in de plaats
                naaldBeginPos++;

            }
        }
    }

    return locaties;
}
