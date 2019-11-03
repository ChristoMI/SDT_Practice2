#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "Country.h"

#define CASE "Case"

#define SPACE ' '

#define LOWER_THRESH 1
#define UPPER_THRESH 10
#define PLACEMENT_DIFFERENCE 1

#define COORDINATES_UNAPPROPRIATE 0
#define COORDINATES_APPROPRIATE 1

#define INTERSECTION_NOT_FOUND 0
#define INTERSECTION_FOUND 1

typedef void InitializerOperationState;

class Initializer {
private:
	int checkCountries(Countries&);

	int checkCoordinates(Coordinates);
	int checkIntersection(Country*, Country*);
public:
	Initializer();
	virtual ~Initializer();

	InitializerOperationState initData(std::vector<string>&, std::vector<Countries>&, string);
};

