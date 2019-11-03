#include "pch.h"
#include "Initializer.h"


#include "Initializer.h"

Initializer::Initializer() {
	// TODO Auto-generated constructor stub

}

Initializer::~Initializer() {
	// TODO Auto-generated destructor stub
}

int Initializer::checkCoordinates(Coordinates coordinates) {
	for (auto coordinate : coordinates) {
		if (coordinate < LOWER_THRESH || coordinate > UPPER_THRESH)
			return COORDINATES_UNAPPROPRIATE;
	}
	
	return COORDINATES_APPROPRIATE;
}

int Initializer::checkIntersection(Country* c1, Country* c2) {
	if ((c1->getxL() >= c2->getxR() && c1->getyL() <= c2->getyR()) ||
		(c1->getxR() <= c2->getxL() && c1->getyL() <= c2->getyR()) ||
		(c1->getxR() <= c2->getxL() && c1->getyR() >= c2->getyL()) ||
		(c1->getxL() >= c2->getxR() && c1->getyR() >= c2->getyL()))
		return INTERSECTION_FOUND;

	return INTERSECTION_NOT_FOUND;
}

InitializerOperationState Initializer::checkCountries(Countries& countries) {
		for (auto country : countries) {
			if (!checkCoordinates(country->getCoordinates())) {
				countries.clear();

				return;
			}
		}

		for (int i = 0; i < countries.size(); i++) {
			Countries otherCountries = countries;
			otherCountries.erase(otherCountries.begin() + i);

			for (auto country : otherCountries) {
				if (checkIntersection(countries[i], country)) {
					countries.clear();

					return;
				}
			}
		}
}

InitializerOperationState Initializer::initData(std::vector<string>& cases, std::vector<Countries>& countriesDB, string filePath) {
	std::ifstream initFile(filePath);
	string buffer;

	while (std::getline(initFile, buffer)) {
		if (buffer.find(CASE) != string::npos)
		{
			cases.push_back(buffer);

			countriesDB.push_back(Countries());
		}
		else {
			std::vector<string> splitResult;

			std::stringstream splitter(buffer);

			string token = "";
			while (std::getline(splitter, token, SPACE)) {
				splitResult.push_back(token);
				token = "";
			}

			countriesDB.back().push_back(new Country(splitResult));
		}

		checkCountries(countriesDB.back());
	}
}