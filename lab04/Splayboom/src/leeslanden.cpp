#include "leeslanden.h"
#include <string>
#include <vector>
#include "splayboom.h"

std::vector<landen::wedstrijd> readCSV(const std::string &bestandsnaam)
{
	std::vector<landen::wedstrijd> vec_wedstrijden;
	Splayboom<string, int> landen;
	std::ifstream csvFile;
	csvFile.open(bestandsnaam.c_str());

	if (!csvFile.is_open())
	{
		std::cout << "Fout pad naar bestand!!!!" << std::endl;
		exit(EXIT_FAILURE);
	}
	string line;
	getline(csvFile, line); // skip the 1st line
	while (getline(csvFile, line))
	{
		if (line.empty()) // skip empty lines:
		{
			continue;
		}

		std::istringstream iss(line);
		std::string lineStream;

		std::vector<std::string> row;

		while (getline(iss, lineStream, ','))
		{
			row.push_back(lineStream);
		}
		int score_home = std::stoi(row[3]);
		int score_away = std::stoi(row[4]);
		std::string winner = row[1];
		if (score_away > score_home)
		{
			winner = row[2];
		}
		else if (score_away == score_home)
		{
			winner = "gelijkspel";
		}
		landen::wedstrijd wedstr = {row[1], row[2], score_home, score_away, winner};
		vec_wedstrijden.push_back(wedstr);
	}
	return vec_wedstrijden;
}

Splayboom<string, int> doelpunten(std::vector<landen::wedstrijd> wedstrijden)
{
	Splayboom<string, int> boom;
	for(const auto& wedstrijd : wedstrijden){
		if(boom.zoekSleutel(wedstrijd.thuisploeg) == true){
			boom.get()->data += wedstrijd.thuisscore;
		}
		else{
			boom.voegtoe(wedstrijd.thuisploeg, wedstrijd.thuisscore);
		}

		if(boom.zoekSleutel(wedstrijd.bezoekers) == true){
			boom.get()->data += wedstrijd.bezoekersscore;
		}
		else{
			boom.voegtoe(wedstrijd.bezoekers, wedstrijd.bezoekersscore);
		}
	}
	return boom;
}

Splayboom<string, int> overwinningen(std::vector<landen::wedstrijd> wedstrijden)
{
	Splayboom<string, int> boom;
	for(const auto& wedstrijd : wedstrijden){
		if(wedstrijd.thuisscore > wedstrijd.bezoekersscore){
			if(boom.zoekSleutel(wedstrijd.thuisploeg) == true){
				boom.get()->data += 1;
			}
			else{
				boom.voegtoe(wedstrijd.thuisploeg, 1);
			}
		}
		else if(wedstrijd.thuisscore < wedstrijd.bezoekersscore){
			if(boom.zoekSleutel(wedstrijd.bezoekers) == true){
				boom.get()->data += 1;
			}
			else{
				boom.voegtoe(wedstrijd.bezoekers, 1);
			}
		}
		else /*if(wedstrijd.thuisscore == wedstrijd.bezoekersscore)*/{
			if(boom.zoekSleutel("gelijkspel") == true){
				boom.get()->data += 1;
			}
			else{
				boom.voegtoe("gelijkspel", 1);
			}
		}

		
	}
	return boom;
}