#pragma once
#include <iostream>
#include <algorithm>
#include <initializer_list>

#include "Country.h"

#define X_COORDS 0
#define Y_COORDS 1

#define COMPLETE_STATE_VALUE 1

#define SINGLE_COUNTRY 1

#define NEIGHBOR_OFFSET 1

typedef void MapOperationState;

class DiffusionMap {
private:
	City*** map;

	int rows;
	int columns;

	CompletionState state;
private:
	MapOperationState generateField(std::pair<Coordinates, Coordinates>);

	MapOperationState initCities(Countries&);
	std::pair<Coordinates, Coordinates> composeCoordinates(Countries);
public:
	DiffusionMap();
	virtual ~DiffusionMap();

	MapOperationState initStructure(Countries&);

	CompletionState shuffle(Countries&);

	CompletionState isCompleted();
};

