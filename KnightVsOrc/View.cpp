#include <iostream>
#include <Windows.h>
#include <map>

#include "View.h"
#include "TitleScreen.h"
#include "GeneralTypes.h"

View::View()
{ 
	this->context = GeneralTypes::ViewList::TitleScreen;
}

View::View(GeneralTypes::ViewList context)
{
	this->context = context;
}


View::View(const View& v) {
	this->context = v.context;
}

void View::clearScreen() {
	std::cout << std::flush;
	system("CLS");
}

void View::render(const std::string toDisplay)
{
	clearScreen();
	std::cout << toDisplay << std::endl;

}

void View::setContext(const GeneralTypes::ViewList context)
{
	this->context = context;
}

const GeneralTypes::ViewList View::getContext()
{
	return this->context;
}

View& View::operator=(View& v)
{
	context = v.context;

	return (*this);
}