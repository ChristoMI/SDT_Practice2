#include "pch.h"
#include "Initializer.h"


#include "Initializer.h"

int Initializer::checkCoordinates(Coordinates coordinates) {
	if (coordinates.size() == BANK_SIZE) {
		for (auto coordinate : coordinates) {
			if (coordinate < LOWER_THRESH - PLACEMENT_DIFFERENCE || coordinate > UPPER_THRESH - PLACEMENT_DIFFERENCE)
				return COORDINATES_UNAPPROPRIATE;
		}
	}
	
	return COORDINATES_APPROPRIATE;
}

int Initializer::checkIntersection(Country& c1, Country& c2) {
	return ((c1.getyL() <= c2.getyL() && c1.getyR() >= c2.getyR()) ||
		(c1.getyL() <= c2.getyR() && c1.getyR() >= c2.getyR())) &&
		((c1.getxR() <= c2.getxR() && c1.getxL() >= c2.getxR()) ||
		(c1.getxR() <= c2.getxL() && c1.getxL() >= c2.getxL()));
}

int Initializer::checkCountries(Countries& countries) {
		for (auto country : countries) {
			if (!checkCoordinates(country->getCoordinates())) {
				countries.clear();

				return 0;
			}
		}

		for (int countryID = 0; countryID < countries.size(); countryID++) {
			Countries otherCountries = countries;
			otherCountries.erase(otherCountries.begin() + countryID);

			for (auto country : otherCountries) {
				if (checkIntersection(*countries[countryID], *country)) {
					countries.clear();

					return 0;
				}
			}
		}

		return 1;
}

InitializerOperationState Initializer::initData(std::vector<string>& cases, std::vector<Countries>& countriesDB, string filePath) {
	std::ifstream initFile(filePath);
	string buffer;

	int casesCounter = 0;

	// Pre-initialization required
	std::getline(initFile, buffer);
	cases.push_back(buffer);
	countriesDB.push_back(Countries());

	while (std::getline(initFile, buffer)) {
		if (buffer.find(CASE) != string::npos)
		{
			if (!checkCountries(countriesDB.back()))
			{
				countriesDB.erase(countriesDB.begin() + casesCounter);
				cases.erase(cases.begin() + casesCounter);

				casesCounter--;
			}

			cases.push_back(buffer);

			countriesDB.push_back(Countries());

			casesCounter++;
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
	}

	if (!checkCountries(countriesDB.back()))
	{
		countriesDB.erase(countriesDB.begin() + casesCounter);
		cases.erase(cases.begin() + casesCounter);

		casesCounter--;
	}
}