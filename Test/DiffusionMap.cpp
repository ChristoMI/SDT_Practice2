#include "pch.h"
#include "DiffusionMap.h"

DiffusionMap::DiffusionMap() {
	// TODO Auto-generated constructor stub

}

DiffusionMap::~DiffusionMap() {
	for (int i = 0; i < this->rows; i++)
		delete map[i];

	delete map;
}

std::pair<Coordinates, Coordinates> DiffusionMap::composeCoordinates(Countries countries) {
	Coordinates xH;
	Coordinates yH;

	for (int i = 0; i < countries.size(); i++) {
		xH.push_back(countries[i]->getxL());
		yH.push_back(countries[i]->getyR());
	}

	return { xH, yH };
}

MapOperationState DiffusionMap::generateField(std::pair<Coordinates, Coordinates> coordinates) {
	this->rows = *(std::max_element(coordinates.first.begin(), coordinates.first.end())) + 1;
	this->columns = *(std::max_element(coordinates.second.begin(), coordinates.second.end())) + 1;

	map = new City**[this->rows];

	for (int i = 0; i < this->rows; i++)
		map[i] = new City*[this->columns]{ NULL };
}

MapOperationState DiffusionMap::initCities(Countries& countries) {
	for (int i = 0; i < countries.size(); i++) {
		for (int k = countries[i]->getxR(); k <= countries[i]->getxL(); k++) {
			for (int j = countries[i]->getyL(); j <= countries[i]->getyR(); j++)
				map[k][j] = new City(countries.size(), i);
		}
	}

	for (int i = 0; i < countries.size(); i++) {
		for (int k = countries[i]->getxR(); k <= countries[i]->getxL(); k++) {
			for (int j = countries[i]->getyL(); j <= countries[i]->getyR(); j++)
			{
				if (k > 0 && map[k - 1][j] != NULL)
					map[k][j]->addNeighbor(map[k - 1][j]);

				if (k < this->rows - 1 && map[k + 1][j] != NULL)
					map[k][j]->addNeighbor(map[k + 1][j]);

				if (j > 0 && map[k][j - 1] != NULL)
					map[k][j]->addNeighbor(map[k][j - 1]);

				if (j < this->columns - 1 && map[k][j + 1] != NULL)
					map[k][j]->addNeighbor(map[k][j + 1]);
			}
		}

	}
}

MapOperationState DiffusionMap::initStructure(Countries& countries) {
	generateField(composeCoordinates(countries));

	state = 1 - countries.size();

	initCities(countries);

}

CompletionState DiffusionMap::isCompleted() {
	return (CompletionState)(state == COMPLETED);
}

CompletionState DiffusionMap::shuffle(Countries& countries) {
	/*std::cout << "______________CASE MAP_____________________" << "\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if(map[i][j] != NULL)
				std::cout << map[i][j]->getNeighborsNumber() << '\t';
			else
				std::cout << '*' << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';*/

	if (countries.size() == 1 || countries.size() == 0)
		return (CompletionState)(state == COMPLETED);
	else
	{
		while (!isCompleted())
		{
			for (auto &country : countries)
				for (int i = country->getxR(); i <= country->getxL(); i++)
					for (int j = country->getyL(); j <= country->getyR(); j++)
						map[i][j]->exportCoins();

			for (auto &country : countries) {
				int currentCountryStatus = country->isCompleted();

				for (int i = country->getxR(); i <= country->getxL(); i++) {
					for (int j = country->getyL(); j <= country->getyR(); j++) {
						int currentCityStatus = map[i][j]->isCompleted();

						map[i][j]->importCoins();

						if (currentCityStatus != map[i][j]->isCompleted())
							country->update();

					}
				}

				if (currentCountryStatus != country->isCompleted())
				{
					state++;
					country->increaseSteps();
				}
				else if (country->isCompleted() != COMPLETED)
					country->increaseSteps();

			}
		}
	}
	
	/*std::cout << "______________CASE MAP_____________________" << "\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if(map[i][j] != NULL)
				std::cout << map[i][j]->showCoins() << '\t';
			else
				std::cout << '*' << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';*/

	return (CompletionState)(state == COMPLETED);
}