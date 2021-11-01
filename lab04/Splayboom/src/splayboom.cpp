#include "splayboom.h"
#include "leeslanden.h"
#include <vector>
#include <string>

int main()
{
	{
		auto wedstrijden = readCSV("voetbal_resultaten.csv");

		Splayboom<std::string, int> doelp = doelpunten(wedstrijden);
		Splayboom<std::string, int> overw = overwinningen(wedstrijden);

		int aantalLanden = overw.aantalKnopen();
		std::cout << "aantal landen is gelijk aan : " << aantalLanden << std::endl;

		std::array<std::string, 10> scenario1 = {"gelijkspel", "France", "Faroe Islands", "France", "Gambia", "Greece", "Finland", "gelijkspel", "gelijkspel", "gelijkspel"};
		std::array<std::string, 10> scenario2 = {"gelijkspel", "Belgium", "France", "United States", "Canada", "Russia", "China", "gelijkspel", "Belgium", "England"};
		std::array<std::string, 10> scenario3 = {"gelijkspel", "Faroe Islands", "Finland", "France", "France", "Gambia", "gelijkspel", "gelijkspel", "gelijkspel", "Greece"};

		auto onderzoek = [&](std::array<std::string, 10> scenario){
			overw.resetDoorzochteDiepte();
			doelp.resetDoorzochteDiepte();
			for (auto i : scenario)
			{
				overw.zoekSleutel(i);
				doelp.zoekSleutel(i);
				//std::cout << i << " heeft " << doelp.get()->sleutel << "doelpunten" << std::endl;
				//std::cout << i << " heeft " << overw.get()->sleutel << "overwiningen" << std::endl;
			}
			std::cout << "overw totale diepte: " << overw.getDoorzochteDieptie() << "\t gem: " << overw.getDoorzochteDieptie() /10 << "\n";
			std::cout << "doelp totale diepte: " << doelp.getDoorzochteDieptie() << "\t gem: " << doelp.getDoorzochteDieptie() /10 << "\n";
			

		};
		
		onderzoek(scenario1);
		onderzoek(scenario2);
		onderzoek(scenario3);

	}
}
