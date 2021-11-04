#pragma once
#include <vector>
#include <string>

#include "CreateCustomFight.h"
class WeaponSettings
{
public:
	WeaponSettings();
	~WeaponSettings();

	enum class Action {
		Create = 0,
		Delete = 1
	};

	std::string getTextToDisplay();
	void reset(CreateCustomFight* f);

	// Used for CREATE
	void addChar(char c);
	void removeChar();

	bool hasMore();
	void nextMenu(CreateCustomFight* f);
	void validate(CreateCustomFight* f);

	void setAction(Action a);
	const Action getAction();

	const int getSelector();

	// Used for DELETE
	bool canDelete();
	void deleteWeapon(CreateCustomFight* f);

	void toggleUp();
	void toggleDown();

private:
	std::vector <std::string> menu;
	std::vector <std::string> answer;

	std::vector <std::string> nameList;
	std::vector <std::vector<std::string>> weaponDescList;

	const std::string baseString = R"(                                                                                                                   )";

	Action action;
	std::string error = "";

	int currentChoice = 0;
	int maxChoice = 0;

	int currentSelector = 0;
	const int maxSelector = 2;
	const int maxWeaponCount = 29;
};

