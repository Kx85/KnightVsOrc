#include "FightBeginScreen.h"
#include "GeneralTypes.h"

std::string FightBeginScreen::updateWithChar(std::string text, Fight* f, const int index) {
	std::string result = text;
	std::string character = "";
	int position = 0;
	for (int i = 0; i < 2; i++) {
		position = (int)((i * 2 + 1) * text.size() / 4);
		switch (f->getPlayer(i)->getType()) {
		case GeneralTypes::Class::Knight:
			character = this->knight.at(index);
			break;
		case GeneralTypes::Class::Orc:
			character = this->orc.at(index);
			break;
		case GeneralTypes::Class::Custom:
			character = this->custom.at(index);
			break;
		}

		result.replace(position - character.size() / 2, character.size(), character);
	}
	return result;
}

const std::string FightBeginScreen::getTextToDisplay(Fight* f)
{

	std::string text = "";
	unsigned int i = 0;
	for (i = 0; i < this->text.size(); i++) {
		std::string toUpdate = this->text.at(i);
		toUpdate = updateWithChar(toUpdate, f, i);
		text = text + "\n" + toUpdate;
	}

	return text;
}