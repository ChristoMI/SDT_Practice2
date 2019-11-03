#pragma once
#include <iostream>
#include <string>
#include "City.h"

#define X_L 0
#define Y_L 1
#define X_R 2
#define Y_R 3

#define NAME_POS 0
#define X_L_POS 1

typedef std::string string;

typedef int Coordinate;
typedef std::vector<Coordinate> Coordinates;

typedef void CountryOperationState;

class Country {
private:
	Coordinates area = std::vector<Coordinate>();
	City** cities;

	CompletionState state;
	int completionSteps;

	string name;

	CountryOperationState swap(Coordinate&, Coordinate&);
public:

	Country();

	Country(std::vector<string>);

	virtual ~Country();

	Coordinate getxR();
	Coordinate getyR();

	Coordinate getxL();
	Coordinate getyL();

	string getName();

	int getSteps();

	Coordinates getCoordinates();

	CountryOperationState update();

	CompletionState isCompleted();

	CountryOperationState increaseSteps();

	static int comparator(Country*, Country*);
};

typedef std::vector<Country*> Countries;