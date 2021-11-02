#include "ExitConfirmBox.h"

const std::string ExitConfirmBox::getTextToDisplay()
{
	resetSelection();
	updateDisplay();

	std::string text = "";
	int i = 0;
	for (i = 0; i < exitConfirmBox.size(); i++) {
		text = text + "\n" + exitConfirmBox.at(i);
	}

	return text;
}

void ExitConfirmBox::toggleChoice()
{
	choice = (choice + 1) % 2;
}

const int ExitConfirmBox::getChoice()
{
	return this->choice;
}

void ExitConfirmBox::updateDisplay()
{
	std::string currentLine = exitConfirmBox.at(6);
	std::size_t found = currentLine.find('[');
	if (choice == 0)
		exitConfirmBox.at(6).replace(exitConfirmBox.at(6).find('[') + 1, 1, "X");
	else
		exitConfirmBox.at(6).replace(exitConfirmBox.at(6).find('[', found + 1) + 1, 1, "X");
}

void ExitConfirmBox::resetSelection()
{
	std::string currentLine = exitConfirmBox.at(6);
	std::size_t found = currentLine.find('[');
	exitConfirmBox.at(6).replace(exitConfirmBox.at(6).find('[') + 1, 1, " ");
	exitConfirmBox.at(6).replace(exitConfirmBox.at(6).find('[', found+1) + 1, 1, " ");
}
