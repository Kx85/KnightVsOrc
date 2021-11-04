#include "SettingsModeWindow.h"

SettingsModeWindow::SettingsModeWindow()
{
	this->choice = 0;
	this->maxChoice = 5;
	this->resetSelection(MenuOptions::Base);
	this->updateDisplay();
}

SettingsModeWindow::~SettingsModeWindow()
{
}

const std::string SettingsModeWindow::getTextToDisplay()
{
	return this->getTextToDisplay(this->lastSelected);
}

const std::string SettingsModeWindow::getTextToDisplay(SettingsModeWindow::MenuOptions menu)
{
	resetSelection(menu);
	updateDisplay();

	return "\n\n\n\n\n\n\n\n\n\n\n\n\n" + cmodeText;
}

void SettingsModeWindow::toggleRightChoice()
{
	this->choice = (this->choice + 1) % this->maxChoice;
}

void SettingsModeWindow::toggleLeftChoice()
{
	if (this->choice == 0) {
		this->choice = this->maxChoice - 1;
	}
	else {
		this->choice--;
	}
}

const int SettingsModeWindow::getChoice()
{
	return this->choice;
}

const SettingsModeWindow::MenuOptions SettingsModeWindow::getLastSelected()
{
	return this->lastSelected;
}

bool SettingsModeWindow::hasNextMenu()
{
	bool hasNext = false;
	switch (this->lastSelected) {
	case MenuOptions::Base:
		hasNext = true;
		this->lastSelected = static_cast<MenuOptions>(this->getChoice() + 1);
		this->choice = 0;
		break;
	}
	return hasNext;
}

bool SettingsModeWindow::hasPreviousMenu()
{
	bool hasPrevious = false;

	switch (this->lastSelected) {
	case MenuOptions::Abilities:
	case MenuOptions::Characters:
	case MenuOptions::Weapons:
		hasPrevious = true;
		this->lastSelected = MenuOptions::Base;
		this->choice = 0;
		break;
	}

	return hasPrevious;
}

void SettingsModeWindow::updateDisplay()
{
	std::size_t found  = 0;
	int index = 0;

	while (index != this->getChoice())
	{
		found += 1;
		found = cmodeText.find('[', found);
		index++;
	}
	cmodeText.replace(cmodeText.find('[', found + 1) + 1, 1, "X");
}

void SettingsModeWindow::resetSelection(SettingsModeWindow::MenuOptions menu)
{
	this->lastSelected = menu;
	this->maxChoice = 0;

	std::size_t found = 0;
	int index = 0;

	cmodeText = modes.at(static_cast<int>(menu));

	while (found != std::string::npos) {
		found += 1;
		found = cmodeText.find('[', found);
		if (found != std::string::npos) {
			this->maxChoice++;
		}
	}

	cmodeText.replace(cmodeText.find('[') + 1, 1, " ");
	while (index != maxChoice)
	{
		found += 1;
		found = cmodeText.find('[', found);
		cmodeText.replace(cmodeText.find('[', found + 1) + 1, 1, " ");
		index++;
	}
}
