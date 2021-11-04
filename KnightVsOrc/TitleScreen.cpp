#include <iostream>
#include <string>

#include "TitleScreen.h"

const std::string TitleScreen::getTextToDisplay()
{
	resetTitleScreenSelection();
	updateTitleScreenDisplay();

	std::string text = "";
	unsigned int i = 0;
	for (i = 0; i < unsigned int(titleSize); i++) {
		text = text + "\n" + titleScreen.at(i);
	}

	for (int k = titleSize; k < choiceOffset; k++) {
		text = text + "\n";
	}

	for (i = titleSize; i < titleScreen.size(); i++) {
		text = text + titleScreen.at(i);
		for (int k = 0; k < menuChoiceOffset; k++) {
			text = text + "\n";
		}
	}

	return text;
}

void TitleScreen::resetTitleScreenSelection() {
	for (unsigned int index = titleSize; index < titleScreen.size(); index++) {
		titleScreen.at(index).replace(titleScreen.at(index).find('[') + 1, 1, " ");
	}
}

void TitleScreen::updateTitleScreenDisplay()
{
	int index = choice + titleSize;
	titleScreen.at(index).replace(titleScreen.at(index).find('[') + 1, 1, "X");
}

void TitleScreen::toggleUpChoice()
{
	if (this->choice == 0) {
		this->choice = this->menuChoice - 1;
	}
	else {
		this->choice--;
	}
}

void TitleScreen::toggleDownChoice()
{
	choice = (choice + 1) % menuChoice;
}

const int TitleScreen::getChoice()
{
	return this->choice;
}
