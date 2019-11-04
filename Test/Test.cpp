#include "pch.h"
#include <iostream>

#include "ConfigData.h"
#include "Displayer.h"

Initializer* initializer = new Initializer();

std::vector<string> cases;
std::vector<Countries> countriesDB;

DiffusionMap* map = new DiffusionMap();

Displayer* displayer = new Displayer();

void clearMemory();

int main()
{
	initializer->initData(cases, countriesDB, INIT_DATA_PATH);

	for (int i = 0; i < cases.size(); i++)
	{
		map->initStructure(countriesDB[i]);

		map->shuffle(countriesDB[i]);

		sort(countriesDB[i].begin(), countriesDB[i].end(), Country::comparator);

		displayer->display(cases[i], countriesDB[i]);
	}

	clearMemory();
}

void clearMemory() {
	for (int i = 0; i < countriesDB.size(); i++)
		for (int j = 0; j < countriesDB[i].size(); j++)
			delete countriesDB[i][j];

	delete map;
	delete initializer;
	delete displayer;
}