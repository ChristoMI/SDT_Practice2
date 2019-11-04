#include "pch.h"
#include "City.h"


#include "City.h"

City::City() {
	// TODO Auto-generated constructor stub

}

City::~City() {
	// TODO Auto-generated destructor stub
}

int City::getNeighborsNumber()
{
	return neighbors.size();
}

City::City(int capacity, int id) {
	for (int coinID = 0; coinID < capacity; coinID++) {
		bank.push_back(0);
		imported.push_back(0);
	}

	state = DEFAULT_STATE - (capacity - DEFAULT_STATE);

	bank[id] = BASE_VALUE;
}

OperationState City::addNeighbor(City* newNeighbor) {
	neighbors.push_back(newNeighbor);
}

OperationState City::exportCoins() {
	for (int coinID = 0; coinID < bank.size(); coinID++) {
		int change = bank[coinID] / THRESHOLD_VALUE;

		for (auto &neighbor : neighbors) {
			neighbor->addImport(change, coinID);
			bank[coinID] -= change;
		}
	}

}

OperationState City::importCoins() {
	for (int coinID = 0; coinID < bank.size(); coinID++)
	{
		if (bank[coinID] == 0 && imported[coinID] != 0)
			state++;

		bank[coinID] += imported[coinID];
		imported[coinID] = 0;
	}
}

OperationState City::addImport(int change, int coinID) {
	imported[coinID] += change;
}

CompletionState City::isCompleted() {
	return (int)(state == 1);
}