#pragma once
#include <vector>
#include <string>

#include "CreateCustomFight.h"
class CreateWeapon
{
public:
	CreateWeapon();
	~CreateWeapon();

	std::string getTextToDisplay();

	void addChar(char c);
	void removeChar();

	bool hasMore();
	void nextMenu(CreateCustomFight* f);
	void validate(CreateCustomFight* f);

	const int getSelector();
	void reset();

private:
	std::vector <std::string> menu;
	std::vector <std::string> answer;

	std::string error = "";

	int currentSelector = 0;
	const int maxSelector = 2;

};

