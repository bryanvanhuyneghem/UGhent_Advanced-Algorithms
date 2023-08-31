/* 
Mogelijke oplossing vraag Rabin Karp Test 2 2020-2021
*/
#include <iostream>
#include <queue>
#include <string>
using std::cout;
using std::queue;
using std::string;

const int ALFABET_GROOTTE = 256;

/* verschillende mogelijkheden om vergelijken te implementeren */
bool is_gelijk(const string &naald, const string &hooiberg, int hooiberg_start) {
    int j = 0;
    for (; j < naald.size() && naald[j] == hooiberg[hooiberg_start + j]; j++) {
    }
    return j == naald.size();
}

queue<int> zoek_rabinkarp(const string &naald, const string &hooiberg, int priemgetal = 997) {
    int lenNaald = naald.size();
    int laatste = hooiberg.size() - naald.size();
    if (laatste < 0)
        return {};

    /* Bereken de fingerprint van de naald */
    int fingerprintNaald = 0;
    for (char c : naald) {
        // bij elk karakter huidige fingerprint vermenigvuldigen met alfabet_grootte en nieuw karakter erbij optellen om overflow te vermijden, telkens modulo nemen
        fingerprintNaald = ((fingerprintNaald * ALFABET_GROOTTE) + (int)c) % priemgetal;
    }
    /* Opmerking: Als de fingerprints systematisch verkeerd berekend worden, zullen bij implementaties zonder rolling hash toch juiste resultaten gevonden worden*/

    /* Bereken de eerste fingerprints in de hooiberg */
    int fingerprintHooiberg = 0;
    for (int i = 0; i < lenNaald; i++) {
        fingerprintHooiberg = ((fingerprintHooiberg * ALFABET_GROOTTE) + (int)hooiberg[i]) % priemgetal;
    }

    /* bereken hulp variabele voor rolling hash d^(p-1) */
    int rest = 1;
    for (int i = 0; i < lenNaald - 1; i++) {
        rest = (rest * ALFABET_GROOTTE) % priemgetal;
    }

    queue<int> resultaten;
    /* voor elk karakter tot hooiberg.size() - naald.size() fingerprints nakijken en nieuwe fingerprint berekenen via rolling hash */
    for (int i = 0; i < laatste; i++) {
        /* vergelijken van fingerprints, indien gelijk moet er nog effectief nagekeken worden of het deel van de hooiberg ook effectief overeenkomt met de naald */
        if (fingerprintHooiberg == fingerprintNaald && is_gelijk(naald, hooiberg, i)) {
            /* positie toevoegen */
            resultaten.push(i);
        }
        /* Rolling hash via cfr. formule onderaan pagina 127 */
        fingerprintHooiberg = ((fingerprintHooiberg + priemgetal * (ALFABET_GROOTTE - 1) - hooiberg[i] * rest) % priemgetal) * ALFABET_GROOTTE + hooiberg[i + lenNaald];
        fingerprintHooiberg %= priemgetal;
    }

    /* fingerprints van de laatste rolling hash testen en eventueel positie toevoegen */
    if (fingerprintHooiberg == fingerprintNaald && is_gelijk(naald, hooiberg, laatste)) {
        resultaten.push(laatste);
    }
    return resultaten;
}

/* hulpfunctie die de queue met resultaten zal afprinten*/
void printPosities(queue<int> posities) {
    int v = -1;
    while (!posities.empty()) {
        v = posities.front();
        posities.pop();
        if (!posities.empty()) {
            std::cout << v << " - ";
        }
    }
    cout << v << "\n";
}

int main() {
    string tekst, naald;
    queue<int> posities;
    cout << "vraag 2: Rabin-Karp \n";

    //voorbeeld 1
    tekst = "Dit is een voorbeeltektst voor de tweede vraag op de test gevorderde algoritmen om het algoritme van Rabin-Karp te testen";
    naald = "algoritme";
    posities = zoek_rabinkarp(naald, tekst);
    printPosities(posities); // 69 - 87

    //voorbeeld 2
    tekst = "38326 25364 25365 25365 38326 25365";
    naald = "25365";
    posities = zoek_rabinkarp(naald, tekst);
    printPosities(posities); // 12 - 18 - 30

    //voorbeeld 3
    posities = zoek_rabinkarp(tekst, naald);
    printPosities(posities); // -1


    std::cout << "Done" << std::endl;
    return 0;
}