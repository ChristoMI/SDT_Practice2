#pragma once
#include <vector>
#include <string>
#define BASE_VALUE 1000000
#define THRESHOLD_VALUE 1000
#define COMPLETED 1
#define DEFAULT_STATE 1


typedef void OperationState;

typedef int CompletionState;

typedef int Coin;
typedef std::vector<Coin> Coins;

class City {
private:
	CompletionState state;

	Coins bank;
	Coins imported;

	OperationState addImport(int, int);

	City() {};
	virtual ~City() {};

	std::vector<City*> neighbors;
public:

	City(int, int);
	
	int getNeighborsNumber();

	OperationState addNeighbor(City*);

	OperationState exportCoins();

	OperationState importCoins();

	CompletionState isCompleted();
};