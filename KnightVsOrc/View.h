#pragma once
#include <string>
#include <map>
#include "GeneralTypes.h"
class View
{
public:
	View();
	View(GeneralTypes::ViewList context);
	View(const View& v);

	void render(const std::string toDisplay);
	void clearScreen();

	void setContext(const GeneralTypes::ViewList context);
	const GeneralTypes::ViewList getContext();
	View& operator=(View& v);

protected:
	int width = 100;
	int height = 23;
	int choice = 0;

private:

	GeneralTypes::ViewList context;
	std::map<GeneralTypes::ViewList, View> viewMap;
};