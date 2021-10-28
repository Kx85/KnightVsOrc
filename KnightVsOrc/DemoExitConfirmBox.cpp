#include "DemoExitConfirmBox.h"

const std::string DemoExitConfirmBox::getTextToDisplay()
{
	resetDemoSelection();
	updateDemoDisplay();

	std::string text = "";
	int i = 0;
	for (i = 0; i < demoExitConfirmBox.size(); i++) {
		text = text + "\n" + demoExitConfirmBox.at(i);
	}

	return text;
}

void DemoExitConfirmBox::toggleChoice()
{
	choice = (choice + 1) % 2;
}

const int DemoExitConfirmBox::getChoice()
{
	return this->choice;
}

void DemoExitConfirmBox::updateDemoDisplay()
{
	std::string currentLine = demoExitConfirmBox.at(6);
	std::size_t found = currentLine.find('[');
	if (choice == 0)
		demoExitConfirmBox.at(6).replace(demoExitConfirmBox.at(6).find('[') + 1, 1, "X");
	else
	demoExitConfirmBox.at(6).replace(demoExitConfirmBox.at(6).find('[', found + 1) + 1, 1, "X");
}

void DemoExitConfirmBox::resetDemoSelection()
{
	std::string currentLine = demoExitConfirmBox.at(6);
	std::size_t found = currentLine.find('[');
	demoExitConfirmBox.at(6).replace(demoExitConfirmBox.at(6).find('[') + 1, 1, " ");
	demoExitConfirmBox.at(6).replace(demoExitConfirmBox.at(6).find('[', found+1) + 1, 1, " ");
}
