#include "stroomnet.h"
#include <iostream>
#include <cassert>
#include <set>

Graaf<ONGERICHT> leesGraaf(std::string bestandsnaam){
    std::ifstream bestand(bestandsnaam);
    if(bestand.is_open()){
        int aantal_knopen = 0;
        bestand >> aantal_knopen;
        Graaf<ONGERICHT> gr(aantal_knopen);
        int van, naar;
        // Verbindingen leggen
        while(bestand >> van){
            bestand >> naar;
            gr.voegVerbindingToe(van, naar);
        }
        return gr;
    }
    return 0;
}

/* Parameters:
        * de graaf zelf
        * de vector van koppels
        * een set dat bijhoudt welke knopen reeds bezocht werden
        * het nummer van de knoop die nu bekeken moet worden tijdens DEZ
        * een boolean die weergeeft of deze knoop al dan niet gekoppeld is
*/
bool heeft_een_vergrotend_k_alternerend_pad(const Graaf<ONGERICHT>& graaf, std::vector<int>& koppels, std::set<int>& bezocht, int knoop, bool isGekoppeld, int start_knoop){
    

    // // tweede eindconditie: stoppen als er een knoop zonder partner gevonden wordt op dit pad && loops vermijden
    if(koppels[knoop] == -1 && knoop != start_knoop){
        return true;
    }
    // eerste eindconditie: stoppen als alle knopen van de graaf gecheckt zijn en er geen andere knoop zonder partner bestaat, of,
    // als de knoop reeds gecontroleerd is
    
    bezocht.insert(knoop);


    // Overloop Burenlijst van knoop en voer het vergrotend k-alternerend pad algoritme uit
    for(const auto& buur : graaf[knoop]){
        // Als buur reeds bezocht is, dan voer je het vergrotend k-alternerend pad algoritme niet uit
        if(bezocht.find(buur.first) != bezocht.end()){
            continue;
        }
        
        bool is_huidige_en_buur_gekoppeld = (koppels[knoop] == buur.first);

        if(!isGekoppeld){ // knoop is nog niet gekoppeld, dus volgende (buur) mag niet gekoppeld zijn
            if(!is_huidige_en_buur_gekoppeld){
                if(heeft_een_vergrotend_k_alternerend_pad(graaf, koppels, bezocht, buur.first, !isGekoppeld, start_knoop)){
                    koppels[knoop] = buur.first;
                    koppels[buur.first] = knoop;
                    return true;
                }
            }
        }
        else{ // knoop is wel gekoppeld, dus volgende (buur) moet gekoppeld zijn
            if(is_huidige_en_buur_gekoppeld){
                if(heeft_een_vergrotend_k_alternerend_pad(graaf, koppels, bezocht, buur.first, !isGekoppeld, start_knoop)){
                    koppels[knoop] = -1;
                    return true;
                }
            }
        }
    }
    
    return false;
}

int maakKoppels(const Graaf<ONGERICHT>& graaf){
    std::vector<int> koppels(graaf.aantalKnopen(), -1); // bevat op het einde van deze methode alle koppels

    int aantalKoppels = 0;
    // Stel voor elke niet-gekoppelde knoop (i.e. value -1) een K-alternerend pad op (== boom)
    // Stopcondities:
    //          * alle knopen zitten in de boom
    //          * er bestaat een tweede knoop op dit pad met -1 als value; de paden (takken) moeten van kleur wisselen (== koppels omwisselen)
    for(int i = 0; i < koppels.size(); i++){
        std::set<int> bezocht;
        // Voer algoritme uit voor een niet-gekoppelde knoop en incrementeer het aantal koppels met 1 indien er
        // dergelijk vergrotend K-alternerend pad bestaat
        if(koppels[i] == -1 && heeft_een_vergrotend_k_alternerend_pad(graaf, koppels, bezocht, i, false, i)){
            aantalKoppels++;
        }
    }

    return aantalKoppels;
}

int main()
{
    // Oef 1
    // ***************************************************** Via DEZ; Vergrotend K-alternerend pad:
    
    Graaf<ONGERICHT> graaf = leesGraaf("../bipartitegraaf");
    
    int aantalKoppels = maakKoppels(graaf);
    std::cout << "Aantal koppels *na* zoeken Vergrotend K-Alternerende paden: " << aantalKoppels << std::endl;
    

    // Oef 2
    //***************************************************** Via Stroomnetwerk:
    /* 
    std::ifstream invoer("../bipartitegraaf");

    std::string eersteLijn;
    getline(invoer, eersteLijn);
    int aantalKnopen = std::stoi(eersteLijn);

    // bipartite graaf construeren: linker knopen kunnen alleen maar verbonden zijn met rechter knopen
    GraafMetTakdata<GERICHT, int> g(aantalKnopen);
    // 2 virtuele knopen: bron & sink
    const int bronKnoopNummer = g.voegKnoopToe();
    const int afvoerKnoopNummer = g.voegKnoopToe();

    int vanKnoopNummer; // linker knoop
    int naarKnoopNummer; // rechter knoop
    while (!invoer.eof()) {
        invoer >> vanKnoopNummer;
        invoer >> naarKnoopNummer;

        // alle linkse knopen in de bipartite graaf verbinden met de bronknoop
        if (g.verbindingsnummer(bronKnoopNummer, vanKnoopNummer) < 0) {
            g.voegVerbindingToe(bronKnoopNummer, vanKnoopNummer, 1);
        }

        // alle verbindingen tussen de linker en rechter knopen toevoegen
        if (g.verbindingsnummer(vanKnoopNummer, naarKnoopNummer) < 0) {
            // capaciteit 1 gebruiken: zo zijn de verhogende paden in het stroomnetwerk tussen bron en afvoer tak-disjunct (de paden hebben geen enkele tak gemeen)
            g.voegVerbindingToe(vanKnoopNummer, naarKnoopNummer, 1);
        }

        // alle rechtse knopen in de bipartite graaf verbinden met de afvoerknoop
        if (g.verbindingsnummer(naarKnoopNummer, afvoerKnoopNummer) < 0) {
            g.voegVerbindingToe(naarKnoopNummer, afvoerKnoopNummer, 1);
        }
    }

    // de capaciteit van de maximale stroom in de bipartite graaf tussen bron- en afvoerknopen geeft het maximum aantal paren
    Stroomnetwerk<int> sn(g, bronKnoopNummer, afvoerKnoopNummer);
    int aantalParen = sn.geefStroom().geefCapaciteit();

    std::cout << "Maximum aantal paren: " << aantalParen << std::endl;

    return 0;
    */
}
