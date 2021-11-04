#pragma once
#include <string>
#include <vector>

#include "Fight.h"
class SettingsModeWindow
{
public:
	SettingsModeWindow();
	~SettingsModeWindow();

	enum class MenuOptions {
		Base = 0,
		Weapons = 1,
		Abilities = 2,
		Characters = 3
	};


	const std::string getTextToDisplay();
	void toggleRightChoice();
	void toggleLeftChoice();
	const int getChoice();
	const MenuOptions getLastSelected();

	bool hasNextMenu();
	bool hasPreviousMenu();

private:

	const std::string getTextToDisplay(MenuOptions menu);
	void updateDisplay();
	void resetSelection(MenuOptions menu);

	std::vector<std::string> modes{
		R"(                   [ ] WEAPONS                [ ] ABILITIES               [ ] CHARACTERS)",
		R"(                                [ ] CREATE WEAPON           [ ] DELETE WEAPON)",
		R"(                                [ ] CREATE ABILITY          [ ] DELETE ABILITY)",
		R"(                                [ ] CREATE CHARACTER        [ ] DELETE CHARACTER)"
	};

	std::string cmodeText = "";
	MenuOptions lastSelected;

	int choice;
	int maxChoice;

};

