#include "pch.h"
#include "Displayer.h"


Displayer::Displayer()
{
}


Displayer::~Displayer()
{
}

void Displayer::display(string currentCase, Countries countries) {
	std::cout << currentCase << std::endl;
	for (auto &country : countries)
		std::cout << country->getName() << '\t' << country->getSteps() << std::endl;
}