#include "CreationMode.h"

CreationMode::CreationMode()
{
	this->resetSelection();
	this->updateDisplay();
}

CreationMode::~CreationMode()
{
}

const std::string CreationMode::getTextToDisplay()
{
	resetSelection();
	updateDisplay();

	return "\n\n\n\n\n\n\n\n\n\n\n\n\n" + cmodeText;
}

void CreationMode::toggleRightChoice()
{
	choice = (choice + 1) % maxChoice;
}

void CreationMode::toggleLeftChoice()
{
	if (choice == 0) {
		this->choice = this->maxChoice - 1;
	}
	else {
		choice--;
	}
}

const int CreationMode::getChoice()
{
	return this->choice;
}

void CreationMode::updateDisplay()
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

void CreationMode::resetSelection()
{
	std::size_t found = 0;
	int index = 0;

	cmodeText.replace(cmodeText.find('[') + 1, 1, " ");
	while (index != maxChoice)
	{
		found += 1;
		found = cmodeText.find('[', found);
		cmodeText.replace(cmodeText.find('[', found + 1) + 1, 1, " ");
		index++;
	}
}
