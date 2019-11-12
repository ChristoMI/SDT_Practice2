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

#define DEFAULT_ROWS_VALUE 0
#define DEFAULT_CLMNS_VALUE 0
#define DEFAULT_STATE_VALUE 0

typedef void MapOperationState;

class DiffusionMap {
private:
	std::vector<std::vector<City*>> map;

	int rows;
	int columns;

	CompletionState state;
private:
	MapOperationState generateField(const std::pair<Coordinates, Coordinates>&);

	MapOperationState initCities(Countries&);
	std::pair<Coordinates, Coordinates> composeCoordinates(const Countries&);

	MapOperationState checkNeighbors(const Coordinate&, const Coordinate&);
public:
	DiffusionMap();
	virtual ~DiffusionMap() {};

	MapOperationState initStructure(Countries&);

	CompletionState shuffle(Countries&);

	CompletionState isCompleted();
};

