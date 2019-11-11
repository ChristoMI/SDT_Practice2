#include "pch.h"
#include "City.h"


#include "City.h"

int City::getNeighborsNumber()
{
	return neighbors.size();
}

City::City(int capacity, int id) {
	bank.reserve(capacity);
	bank.assign(capacity, 0);

	imported.reserve(capacity);
	imported.assign(capacity, 0);

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
	if (state == COMPLETED)
		return true;
	else
		return false;
}