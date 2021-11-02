#pragma once
#include <string>
#include <vector>

#include "Fight.h"
class CreationMode
{
public:
	CreationMode();
	~CreationMode();

	const std::string getTextToDisplay();
	void toggleRightChoice();
	void toggleLeftChoice();
	const int getChoice();

private:
	void updateDisplay();
	void resetSelection();

	std::string cmodeText = { R"(     [ ] CREATE WEAPON          [ ] CREATE ABILITY          [ ] CREATE CLASS          [ ] SAVE          [ ] LOAD)" };

	int choice = 0;
	const int maxChoice = 5;

};

