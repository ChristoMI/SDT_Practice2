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
	for (int i = 0; i < capacity; i++) {
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
	for (int i = 0; i < bank.size(); i++) {
		int change = bank[i] / THRESHOLD_VALUE;

		for (auto &neighbor : neighbors) {
			neighbor->addImport(change, i);
			bank[i] -= change;
		}
	}

}

OperationState City::importCoins() {
	for (int i = 0; i < bank.size(); i++)
	{
		if (bank[i] == 0 && imported[i] != 0)
			state++;

		bank[i] += imported[i];
		imported[i] = 0;
	}
}

OperationState City::addImport(int change, int coinID) {
	imported[coinID] += change;
}

CompletionState City::isCompleted() {
	return (int)(state == 1);
}

std::string City::showCoins()
{
	std::string qwe ="";
	for (int i = 0; i < bank.size(); i++)
		qwe +=std::to_string(bank[i]) + "|";

	return qwe;
}
