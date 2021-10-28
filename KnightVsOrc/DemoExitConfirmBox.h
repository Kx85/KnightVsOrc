#pragma once
#include <string>
#include <vector>

class DemoExitConfirmBox
{
public:
	const std::string getTextToDisplay();
	void toggleChoice();
	const int getChoice();

private:
	void updateDemoDisplay();
	void resetDemoSelection();

	std::vector<std::string> demoExitConfirmBox{
R"(+---------------------------------------------------+)",
R"(|                                                   |)",
R"(|                                                   |)",
R"(|        Exit Demo and go back to main menu?        |)",
R"(|                                                   |)",
R"(|                                                   |)",
R"(|            [ ] YES              [ ] NO            |)",
R"(|                                                   |)",
R"(|                                                   |)",
R"(+---------------------------------------------------+)"
	};
	int choice = 0;
};


