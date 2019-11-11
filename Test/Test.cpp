#include "pch.h"
#include <iostream>

#include "ConfigData.h"
#include "Displayer.h"

int main()
{
	Initializer initializer;	
	DiffusionMap map;
	Displayer displayer;
	
	std::vector<string> cases;
	std::vector<Countries> countriesDB;

	initializer.initData(cases, countriesDB, INIT_DATA_PATH);

	for (int caseID = 0; caseID < cases.size(); caseID++)
	{
		map.initStructure(countriesDB[caseID]);

		map.shuffle(countriesDB[caseID]);

		sort(countriesDB[caseID].begin(), countriesDB[caseID].end(), Country::comparator);

		displayer.display(cases[caseID], countriesDB[caseID]);
	}

	for (int caseID = 0; caseID < countriesDB.size(); caseID++)
		for (int countryID = 0; countryID < countriesDB[caseID].size(); countryID++)
			delete countriesDB[caseID][countryID];
}
