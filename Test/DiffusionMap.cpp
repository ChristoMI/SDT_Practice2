#include "pch.h"
#include "DiffusionMap.h"

DiffusionMap::DiffusionMap() {
	this->rows = DEFAULT_ROWS_VALUE;
	this->columns = DEFAULT_CLMNS_VALUE;

	this->state = DEFAULT_STATE_VALUE;
}

std::pair<Coordinates, Coordinates> DiffusionMap::composeCoordinates(const Countries& countries) {
	Coordinates xH;
	Coordinates yH;

	for (int countryID = 0; countryID < countries.size(); countryID++) {
		xH.push_back(countries[countryID]->getxL());
		yH.push_back(countries[countryID]->getyR());
	}

	return { xH, yH };
}

MapOperationState DiffusionMap::generateField(const std::pair<Coordinates, Coordinates>& coordinates) {
	this->rows = *(std::max_element(coordinates.first.begin(), coordinates.first.end())) + 1;
	this->columns = *(std::max_element(coordinates.second.begin(), coordinates.second.end())) + 1;


	for (int i = 0; i < this->rows; i++)
	{
		map.push_back(std::vector<City*>());

		for (int j = 0; j < this->columns; j++)
			map[i].push_back(NULL);
	}
}

MapOperationState DiffusionMap::checkNeighbors(const Coordinate& xPos, const Coordinate& yPos) {
	if (xPos > 0 && map[xPos - NEIGHBOR_OFFSET][yPos] != NULL)
		map[xPos][yPos]->addNeighbor(map[xPos - NEIGHBOR_OFFSET][yPos]);

	if (xPos < this->rows - NEIGHBOR_OFFSET && map[xPos + NEIGHBOR_OFFSET][yPos] != NULL)
		map[xPos][yPos]->addNeighbor(map[xPos + NEIGHBOR_OFFSET][yPos]);

	if (yPos > 0 && map[xPos][yPos - NEIGHBOR_OFFSET] != NULL)
		map[xPos][yPos]->addNeighbor(map[xPos][yPos - NEIGHBOR_OFFSET]);

	if (yPos < this->columns - NEIGHBOR_OFFSET && map[xPos][yPos + NEIGHBOR_OFFSET] != NULL)
		map[xPos][yPos]->addNeighbor(map[xPos][yPos + NEIGHBOR_OFFSET]);
}

MapOperationState DiffusionMap::initCities(Countries& countries) {
	for (int countryID = 0; countryID < countries.size(); countryID++) {
		for (int xPos = countries[countryID]->getxR(); xPos <= countries[countryID]->getxL(); xPos++) {
			for (int yPos = countries[countryID]->getyL(); yPos <= countries[countryID]->getyR(); yPos++)
				map[xPos][yPos] = new City(countries.size(), countryID);
		}
	}

	for (int countryID = 0; countryID < countries.size(); countryID++) 
		for (int xPos = countries[countryID]->getxR(); xPos <= countries[countryID]->getxL(); xPos++) 
			for (int yPos = countries[countryID]->getyL(); yPos <= countries[countryID]->getyR(); yPos++)
				checkNeighbors(xPos, yPos);
	
}

MapOperationState DiffusionMap::initStructure(Countries& countries) {
	generateField(composeCoordinates(countries));

	state = COMPLETE_STATE_VALUE - countries.size();

	initCities(countries);
}

CompletionState DiffusionMap::isCompleted() {
	return state == COMPLETED;
}

CompletionState DiffusionMap::shuffle(Countries& countries) {
	if (countries.size() == SINGLE_COUNTRY)
		return true;
	else
	{
		while (!isCompleted())
		{
			for (auto &country : countries)
				for (int xPos = country->getxR(); xPos <= country->getxL(); xPos++)
					for (int yPos = country->getyL(); yPos <= country->getyR(); yPos++)
						map[xPos][yPos]->exportCoins();

			for (auto &country : countries) {
				bool currentCountryStatus = country->isCompleted();

				for (int xPos = country->getxR(); xPos <= country->getxL(); xPos++) {
					for (int yPos = country->getyL(); yPos <= country->getyR(); yPos++) {
						bool currentCityStatus = map[xPos][yPos]->isCompleted();

						map[xPos][yPos]->importCoins();

						if (currentCityStatus != map[xPos][yPos]->isCompleted())
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

	return state == COMPLETED;
}