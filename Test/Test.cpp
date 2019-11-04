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

	for (int caseID = 0; caseID < cases.size(); caseID++)
	{
		map->initStructure(countriesDB[caseID]);

		map->shuffle(countriesDB[caseID]);

		sort(countriesDB[caseID].begin(), countriesDB[caseID].end(), Country::comparator);

		displayer->display(cases[caseID], countriesDB[caseID]);
	}

	clearMemory();
}

void clearMemory() {
	for (int caseID = 0; caseID < countriesDB.size(); caseID++)
		for (int countryID = 0; countryID < countriesDB[caseID].size(); countryID++)
			delete countriesDB[caseID][countryID];

	delete map;
	delete initializer;
	delete displayer;
}