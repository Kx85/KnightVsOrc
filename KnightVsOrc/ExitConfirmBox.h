#pragma once
#include <string>
#include <vector>

class ExitConfirmBox
{
public:
	const std::string getTextToDisplay();
	void toggleChoice();
	const int getChoice();

private:
	void updateDisplay();
	void resetSelection();

	std::vector<std::string> exitConfirmBox{
R"(                    +---------------------------------------------------+)",
R"(                    |                                                   |)",
R"(                    |                                                   |)",
R"(                    |          Exit and go back to main menu?           |)",
R"(                    |                                                   |)",
R"(                    |                                                   |)",
R"(                    |            [ ] YES              [ ] NO            |)",
R"(                    |                                                   |)",
R"(                    |                                                   |)",
R"(                    +---------------------------------------------------+)"
	};
	int choice = 0;
};


