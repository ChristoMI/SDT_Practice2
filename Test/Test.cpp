#include "pch.h"
#include <iostream>

#include "ConfigData.h"

Initializer* initializer = new Initializer();

std::vector<string> cases;
std::vector<Countries> countryDB;

DiffusionMap* map = new DiffusionMap();

void clearMemory();

int main()
{
	initializer->initData(cases, countryDB, INIT_DATA_PATH);

	for (int i = 0; i < cases.size(); i++)
	{
		map->initStructure(countryDB[i]);

		map->shuffle(countryDB[i]);

		sort(countryDB[i].begin(), countryDB[i].end(), Country::comparator);

		std::cout << cases[i] << std::endl;
		for (auto &country : countryDB[i])
			std::cout << country->getName() << '\t' << country->getSteps() << std::endl;
	}

	clearMemory();
}

void clearMemory() {
	for (int i = 0; i < countryDB.size(); i++)
		for (int j = 0; j < countryDB[i].size(); j++)
			delete countryDB[i][j];

	delete map;
	delete initializer;
}