#include "airbnb.h"
#include <string>

using namespace std;

int main() {
    //toepassing prijs
    Schijf<BKnoop<int, int, 100>> schijf;
    BTree<int, int, 100> boom = leesCSV_prijs("AB_NYC_2019.csv", &schijf);
    int id = 36422573;
    std::cout << "huis gaan zoeken met id: " << id << std::endl;
    if(boom.zoekSleutel(id)){
        auto prijs = boom.geefData(id);
        std::cout << "prijs van deze airbnb: " <<  *prijs << " euro per nacht" << std::endl;
    }
    
    //toepassing huizen
    Schijf<BKnoop<int, hosts::property, 10>> schijf2;
    BTree<int, hosts::property, 10> boom1 = leesCSV("AB_NYC_2019.csv", &schijf2);

    int ids[6] = {36422573,3831,253466,253803,253468, 35372810};
    for(auto id: ids){
        if(boom1.zoekSleutel(id)){
            std::cout << "\n\nhuis met id: " << id << " gevonden" << std::endl;
            auto huis = boom1.geefData(id);
            std::cout << "NAAM: " << huis->name << std::endl;
            std::cout << "BUURT: " << huis->buurt << std::endl;
            std::cout << "PRIJS: " <<huis->prijs << std::endl;
            std::cout << "AANTAL REVIEWS: " << huis->aantalreviews << std::endl;
            std::cout << "BESCHIKBAARHEID: " << huis->beschikbaarheid << std::endl;
        }
        else{
            std::cout << "huis met id: " << id << " niet gevonden" << std::endl;
        }
    }
    
    std::cout << "Done" << std::endl;

    return 0;
}