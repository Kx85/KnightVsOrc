#include <iostream>
#include <Windows.h>

#include "View.h"
#include "GeneralTypes.h"

View::View()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	this->width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	this->height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	this->context = GeneralTypes::ViewList::Menu;
}

View::View(GeneralTypes::ViewList& context)
{
	this->context = context;
}


View::View(const View& v) {
	this->context = v.context;
}

void View::render()
{
	std::cout << std::flush;
	system("CLS");
	switch (this->context) {
	case GeneralTypes::ViewList::Menu:
		this->renderMenu();
		break;
	case GeneralTypes::ViewList::Fight:
		std::cout << "Not yet implemented" << std::endl;
		break;
	default:
		std::cout << "Lel failed" << std::endl;
	}
}

void View::setContext(const GeneralTypes::ViewList& context)
{
	this->context = context;
}

View& View::operator=(View& v)
{
	context = v.context;

	return (*this);
}

void View::toggleChoice()
{
	this->choice = (choice + 1) % 2;
}

void View::renderMenu()
{
	std::cout << R"(
		  _  __          _           _       _      __      __           ____                
		 | |/ /         (_)         | |     | |     \ \    / /          / __ \               
		 | ' /   _ __    _    __ _  | |__   | |_     \ \  / /   ___    | |  | |  _ __    ___ 
		 |  <   | '_ \  | |  / _` | | '_ \  | __|     \ \/ /   / __|   | |  | | | '__|  / __|
		 | . \  | | | | | | | (_| | | | | | | |_       \  /    \__ \   | |__| | | |    | (__ 
		 |_|\_\ |_| |_| |_|  \__, | |_| |_|  \__|       \/     |___/    \____/  |_|     \___|
		                      __/ |                                                          
		                     |___/                                                           
					)" << std::endl;

	std::cout << "\n\n\n\n\n\n\n" << std::endl;

	
	std::string pressStart = "                                                 [ ]  PRESS START                                         ";
	std::string demo       = "                                                 [ ]     DEMO                                             ";

	if (choice == 1) {
		pressStart.replace(pressStart.find('[')+1,1,"X");
	}
	else {
		demo.replace(demo.find('[') + 1, 1, "X");
	}

	std::cout << pressStart << "\n\n" << demo << std::endl;

}
