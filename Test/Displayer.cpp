#include "pch.h"
#include "Displayer.h"

void Displayer::display(const string& currentCase, const Countries& countries) {
	std::cout << currentCase << std::endl;
	for (auto &country : countries)
		std::cout << country->getName() << '\t' << country->getSteps() << std::endl;
}