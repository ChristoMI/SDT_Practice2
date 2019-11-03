#include "pch.h"
#include "Country.h"


#include "Country.h"

Country::Country() {
	// TODO Auto-generated constructor stub

}

CountryOperationState Country::swap(Coordinate& c1, Coordinate& c2) {
	Coordinate t = c1;
	c1 = c2;
	c2 = t;
}

Country::Country(std::vector<string> splitString) {
	name = splitString[NAME_POS];

	for (auto &pos : std::vector<string>(splitString.begin() + X_L_POS, splitString.end()))
		area.push_back(std::stoi(pos) - 1);

	if (area[X_L] < area[X_R]) 
		swap(area[X_L], area[X_R]);
	if(area[Y_L] > area[Y_R])
		swap(area[Y_L], area[Y_R]);

	state = 1 - (area[X_L] - area[X_R] + 1) * (area[Y_R] - area[Y_L] + 1);
}

Country::~Country() {
	// TODO Auto-generated destructor stub
}

Coordinate Country::getxL() {
	return this->area[X_L];
}

Coordinate Country::getyL() {
	return this->area[Y_L];
}

string Country::getName()
{
	return name;
}

int Country::getSteps()
{
	return completionSteps;
}

Coordinate Country::getxR() {
	return this->area[X_R];
}

Coordinate Country::getyR() {
	return this->area[Y_R];
}

Coordinates Country::getCoordinates() {
	Coordinates countryCoordinates{ this->area[X_L], this->area[Y_L], this->area[X_R], this->area[Y_R] };

	return countryCoordinates;
}

CountryOperationState Country::update() {
	state++;
}


CompletionState Country::isCompleted() {
	return (CompletionState)(state == COMPLETED);
}

CountryOperationState Country::increaseSteps() {
	completionSteps++;
}

int Country::comparator(Country* c1, Country* c2) {
	if (c1->completionSteps < c2->completionSteps)
		return 1;
	else if (c1->completionSteps > c2->completionSteps)
		return 0;
	else {
		if (c1->name < c2->name)
			return 1;
		else
			return 0;
	}
}