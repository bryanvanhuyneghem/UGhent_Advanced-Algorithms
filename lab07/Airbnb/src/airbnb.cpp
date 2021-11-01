
#include "airbnb.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

BTree<int, int, 100> leesCSV_prijs(const std::string &bestandsnaam, Schijf<BKnoop<int, int, 100>>* schijf){
    BTree<int, int, 100> boom(*schijf);
    std::ifstream csvFile;
	csvFile.open(bestandsnaam.c_str());
    int teller = 0;
	if (!csvFile.is_open())
	{
		std::cout << "Fout pad naar bestand!!!!" << std::endl;
		exit(EXIT_FAILURE);
	}
	constexpr int id_idx = 0;
	constexpr int price_idx = 9;
	std::string line;
	getline(csvFile, line); // skip the 1st line

	auto csv = readCSV(csvFile);

	for(const auto& row : csv){
		if(row.size() == 16){
			int id = std::stoi(row[id_idx]);
			int prijs = std::stoi(row[price_idx]);
			boom.voegtoe(id, prijs);
			teller++;
		}
	}

    std::cout << teller << " prijzen toegevoegd" << std::endl;
    return boom;
}

BTree<int, hosts::property, 10> leesCSV(const std::string &bestandsnaam, Schijf<BKnoop<int, hosts::property, 10>>* schijf){
    BTree<int, hosts::property, 10> boom(*schijf);

    std::ifstream csvFile;
	csvFile.open(bestandsnaam.c_str());
    int teller = 0;
	if (!csvFile.is_open())
	{
		std::cout << "Fout pad naar bestand!!!!" << std::endl;
		exit(EXIT_FAILURE);
	}

	
	
	constexpr int id_idx = 0;
	constexpr int name_idx = 1;
	constexpr int neighbourhood_idx = 5;
	constexpr int price_idx = 9;
	constexpr int n_reviews_idx = 11;
	constexpr int availability_idx = 15;
	std::string line;
	getline(csvFile, line); // skip the 1st line

	auto csv = readCSV(csvFile);

	for(const auto& row : csv){
		if(row.size() == 16){
			if (std::stoi(row[id_idx]) > 13745575){
				break;
			}
			hosts::property property;
			int id = std::stoi(row[id_idx]);
			//std::cout << id << ": -> naam: " << row[name_idx] << std::endl;
			property.name = row[name_idx];
			property.buurt = row[neighbourhood_idx];
			property.prijs = std::stoi(row[price_idx]);
			property.aantalreviews = std::stoi(row[n_reviews_idx]);
			property.beschikbaarheid = std::stoi(row[availability_idx]);
			boom.voegtoe(id, property);
			teller++;
		}

	}
	
    std::cout << teller << " huizen toegevoegd" << std::endl;
    return boom;
}

enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};

std::vector<std::string> readCSVRow(const std::string &row) {
    CSVState state = CSVState::UnquotedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
std::vector<std::vector<std::string>> readCSV(std::istream &in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}