#pragma once
#include <string>
#include "GeneralTypes.h"
class View
{
public:
	View();
	View(GeneralTypes::ViewList& context);
	View(const View& v);

	void render();

	void setContext(const GeneralTypes::ViewList& context);
	View& operator=(View& v);

	void toggleChoice();

protected:
	int width = 100;
	int height = 23;

private:
	void renderMenu();

	GeneralTypes::ViewList context;
	int choice = 1;
};


