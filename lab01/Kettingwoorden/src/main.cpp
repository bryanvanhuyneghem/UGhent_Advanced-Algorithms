#include "graaf.hpp"
#include "woordspel.cpp"
#include "componenten.cpp"
#include "keten.hpp"

int main()
{
    GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> woorden = leesGraaf("/home/bryan/UGhent_Advanced-Algorithms/lab01/Kettingwoorden/woordenlijst.txt", "/home/bryan/UGhent_Advanced-Algorithms/lab01/Kettingwoorden/takkenlijst.txt");

    std::cout << woorden.aantalVerbindingen() << " verbindingen ingelezen" << std::endl;

    // Stap 1: categoriseer woorden in sterk geconnecteerde componenten
    vector<int> component_nrs = sterk_geconnecteerde_componenten(woorden);

    int max_component_nr = *std::max_element(component_nrs.begin(), component_nrs.end());
    std::cout << "Er zijn " << max_component_nr + 1 << " sterk geconnecteerde componenten\n";

    vector<int> aantal_woorden_per_component(max_component_nr + 1, 0);
    for (int component_nr : component_nrs)
    {
        aantal_woorden_per_component[component_nr]++;
    }

    std::vector<int>::iterator grootste_component = std::max_element(aantal_woorden_per_component.begin(), aantal_woorden_per_component.end());
    int grootste_component_nr = std::distance(aantal_woorden_per_component.begin(), grootste_component);
    int aantal_woorden = *grootste_component;

    cout << "De grootste geconnecteerde component is " << grootste_component_nr
         << " met " << aantal_woorden << " woorden\n";

    Keten eerste_keten = eersteKringKetting(woorden, component_nrs, grootste_component_nr);
    cout << "Eerste keten: " << eerste_keten << endl;
    
    std::cout << "Done..." << std::endl;
}
