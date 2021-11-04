#pragma once
#include <string>
#include <vector>

class TitleScreen
{
public:
	const std::string getTextToDisplay();

	void toggleDownChoice();
	void toggleUpChoice();
	const int getChoice();

private:
	void updateTitleScreenDisplay();
	void resetTitleScreenSelection();

	std::vector<std::string> titleScreen{
		 R"(      _  __          _           _       _      __      __           ____                )",
		 R"(     | |/ /         (_)         | |     | |     \ \    / /          / __ \               )",
		 R"(     | ' /   _ __    _    __ _  | |__   | |_     \ \  / /   ___    | |  | |  _ __    ___ )",
		 R"(     |  <   | '_ \  | |  / _` | | '_ \  | __|     \ \/ /   / __|   | |  | | | '__|  / __|)",
		 R"(     | . \  | | | | | | | (_| | | | | | | |_       \  /    \__ \   | |__| | | |    | (__ )",
		 R"(     |_|\_\ |_| |_| |_|  \__, | |_| |_|  \__|       \/     |___/    \____/  |_|     \___|)",
		 R"(                          __/ |                                                          )",
		 R"(                         |___/                                                           )",
		 R"(                [ ] PRESS START)",
		 R"(                [ ] DEMO)",
		 R"(                [ ] SETTINGS)"
	};

	const int choiceOffset = 16;
	int menuChoice = 3;
	const int menuChoiceOffset = 3;
	const int titleSize = 8;
	int choice = 0;
};

