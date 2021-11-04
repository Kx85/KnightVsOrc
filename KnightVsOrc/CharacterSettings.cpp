#include <regex>

#include "CharacterSettings.h"
#include "GeneralTypes.h"

CharacterSettings::CharacterSettings()
{
	this->action = CharacterSettings::Action::Create;
}

CharacterSettings::~CharacterSettings()
{
}

std::string CharacterSettings::getTextToDisplay()
{
	std::string text = "";
	std::vector<std::string> tmpStrings = std::vector<std::string>(maxCharacterCount, baseString);
	std::size_t found = (size_t)50;

	switch (this->action) {
	case Action::Create:

		for (unsigned int i = 0; i < this->nameList.size(); i++) {
			tmpStrings.at(i + 1).replace(found + 5,
				this->nameList.at(i).size(),
				this->nameList.at(i));
		}

		for (int i = 0; i <= this->currentSelector; i++) {
			tmpStrings.at(i).replace(0, (this->menu.at(i) + " " + this->answer.at(i)).size(), this->menu.at(i) + " " + this->answer.at(i));
			text = text + "\n" + tmpStrings.at(i);
		}

		for (unsigned int i = this->currentSelector + 1; i <= this->nameList.size(); i++) {
			text = text + "\n" + tmpStrings.at(i);
		}
		

		break;
	case Action::Delete:
		// 2 first characters can't be deleted
		tmpStrings.at(0).replace((size_t)5 + this->nameList.at(0).size(),
			14,
			"(Not erasable)");
		tmpStrings.at(1).replace((size_t)8 + this->nameList.at(1).size(),
			14,
			"(Not erasable)");

		// Display Character infos
		for (int i = 0; i < 6; i++) {
			tmpStrings.at(i + 1).replace(found + 5,
				this->characterDescList.at(this->currentChoice).at(i).size(),
				this->characterDescList.at(this->currentChoice).at(i));
		}

		for (int i = 0; i < this->maxChoice; i++) {
			int length = ((int)this->nameList.at(i).size() < 45) ? (int)this->nameList.at(i).size() : 45;

			if (i == this->currentChoice) {
				tmpStrings.at(i).replace(1, 2, "->");
				tmpStrings.at(i).replace(3, length, this->nameList.at(i));
				tmpStrings.at(i).replace((size_t)3 + length, 2, "<-");
			}
			else {
				tmpStrings.at(i).replace(3, length, this->nameList.at(i));
			}
			text = text + "\n" + tmpStrings.at(i);
		}

		for (int i = this->maxChoice; i < maxCharacterCount; i++) {
			text = text + "\n" + tmpStrings.at(i);
		}
		break;
	}

	return text + this->error;
}

void CharacterSettings::addChar(char c)
{
	this->answer.at(currentSelector).push_back(c);
}

void CharacterSettings::removeChar()
{
	if (this->answer.at(currentSelector).size() > 0)
		this->answer.at(currentSelector).pop_back();
	else
		currentSelector--;
}

bool CharacterSettings::hasMore()
{
	return (this->maxSelector - this->currentSelector) >= 0;
}

void CharacterSettings::nextMenu(CreateCustomFight* f)
{

	bool validValue = false;
	error = "";
	switch (this->currentSelector) {
	case 0:
		validValue = !validValue;
		for (int i = 0; i < f->getCharactersSize(); i++) {
			if (f->getCharacters()->at(i).getName() == this->answer.at(currentSelector)) {
				error = "\n(Character name already existing!)\n";
				validValue = !validValue;
				break;
			}
		}
		if (!std::regex_match(this->answer.at(currentSelector), std::regex("[a-zA-Z]+"))) {
			error = "\n(Only letters!)\n";
			validValue = !validValue;
		}
		break;
	case 1:
		for (int i = GeneralTypes::Class::Custom; i != GeneralTypes::Class::ClassCount; i++) {
			if (GeneralTypes::class_str[i] == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}

		if (!validValue)
			error = "\n(Invalid Class Name!)\n";

		break;
	case 2:
		if (std::regex_match(this->answer.at(currentSelector), std::regex("[1-9][0-9]*")))
			validValue = !validValue;
		break;
	case 3:
		if (std::regex_match(this->answer.at(currentSelector), std::regex("[0-9]+")))
			validValue = !validValue;
		break;
	case 4:
		for (int i = 0; i < f->getWeaponsSize(); i++) {
			if (f->getWeapons()->at(i).getName() == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
		break;
	case 5:
		for (int i = 0; i < f->getAbilitiesSize(); i++) {
			if (f->getAbilities()->at(i).getName() == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
		break;
	}

	if (this->currentSelector >= 0 && (this->answer.at(currentSelector) == "Orc" || this->answer.at(currentSelector) == "Knight")) {
		this->currentSelector = this->maxSelector;
	}

	if (validValue) {
		this->nameList.clear();
		this->currentSelector++;
		switch (this->currentSelector) {
		case 1:
			for (int i = GeneralTypes::Class::Custom; i < GeneralTypes::Class::ClassCount; i++) {
				this->nameList.push_back(GeneralTypes::class_str[i]);
			}
			break;
		case 4:
			for (int i = 0; i < f->getCharactersSize(); i++) {
				this->nameList.push_back(f->getWeapons()->at(i).getName());
			}
			break;
		case 5:
			for (int i = 0; i < f->getAbilitiesSize(); i++) {
				this->nameList.push_back(f->getAbilities()->at(i).getName());
			}
			break;
		}

	}
}

void CharacterSettings::validate(CreateCustomFight* f)
{
	GeneralTypes::Class cl = GeneralTypes::Class::Custom;
	Character c = Character();
	int index = -1;


	for (int i = 0; i < f->getCharactersSize(); i++) {
		if (f->getCharacters()->at(i).getName() == this->answer.at(0)) {
			cl = f->getCharacters()->at(i).getType();
			index = i;
			break;
		}
	}

	if (index == -1) {
		for (int i = GeneralTypes::Class::Custom; i != GeneralTypes::Class::ClassCount; i++) {
			for (int k = 0; k < f->getCharactersSize(); k++) {
				if (GeneralTypes::class_str[f->getCharacters()->at(k).getType()] == this->answer.at(1)) {
					cl = f->getCharacters()->at(k).getType();
					index = k;
					break;
				}
			}
		}
	}

	switch (cl) {
	case GeneralTypes::Class::Knight:
	case GeneralTypes::Class::Orc:
		c = f->getCharacters()->at(index);
		c.setName(this->answer.at(0));
		break;
	case GeneralTypes::Class::Custom:
		c.setName(this->answer.at(0));
		c.setType(cl);
		c.setMaxHealth(std::stoi(this->answer.at(2)));
		c.setHealth(std::stoi(this->answer.at(2)));
		c.setMaxShield(std::stoi(this->answer.at(3)));
		c.setShield(std::stoi(this->answer.at(3)));

		for (int i = 0; i < f->getWeaponsSize(); i++) {
			if (this->answer.at(4) == f->getWeapons()->at(i).getName()) {
				c.setWeapon(&f->getWeapons()->at(i));
			}
		}

		for (int i = 0; i < f->getAbilitiesSize(); i++) {
			if (this->answer.at(5) == f->getAbilities()->at(i).getName()) {
				c.setAbility(&f->getAbilities()->at(i));
			}
		}
		break;
	}

	f->getCharacters()->push_back(c);

}

void CharacterSettings::setAction(CharacterSettings::Action a)
{
	this->action = a;
}

const CharacterSettings::Action CharacterSettings::getAction()
{
	return this->action;
}

const int CharacterSettings::getSelector()
{
	return this->currentSelector;
}

void CharacterSettings::reset(CreateCustomFight* f)
{
	std::string str = "";

	switch (this->action) {
	case Action::Create:
		this->currentSelector = 0;
		this->menu.clear();
		this->answer.clear();
		this->nameList.clear();


		for (int i = 0; i < f->getCharactersSize(); i++) {
			this->nameList.push_back(f->getCharacters()->at(i).getName());
		}

		this->menu.push_back("Name:");
		this->answer.push_back("");

		menu.push_back("Class:");
		answer.push_back("");

		menu.push_back("Hp:");
		answer.push_back("");

		menu.push_back("Shield:");
		answer.push_back("");

		menu.push_back("Weapon:");
		answer.push_back("");

		menu.push_back("Ability:");
		answer.push_back("");

		break;
	case Action::Delete:
		this->nameList.clear();
		this->characterDescList.clear();
		this->currentChoice = 0;
		this->maxChoice = f->getCharactersSize();

		for (int i = 0; i < f->getCharactersSize(); i++) {
			std::vector<std::string> descList;
			Character c = f->getCharacters()->at(i);
			std::string weapon = c.getWeapon().getName();
			std::string classType = GeneralTypes::class_str[c.getType()];

			this->nameList.push_back(c.getName());
			descList.push_back("Name    : " + c.getName());
			descList.push_back("Class   : " + classType);
			descList.push_back("Hp      : " + std::to_string(c.getHealth()));
			descList.push_back("Shield  : " + std::to_string(c.getShield()));
			descList.push_back("Weapon  : " + weapon);
			descList.push_back("Ability : " + c.getAbility().getName());
			this->characterDescList.push_back(descList);
		}
	}
}

bool CharacterSettings::canDelete()
{
	return (this->currentChoice > 1) ? true : false;
}

void CharacterSettings::deleteCharacter(CreateCustomFight* f)
{
	auto it = f->getCharacters()->begin() + this->currentChoice;
	f->getCharacters()->erase(it);
	this->reset(f);
}

void CharacterSettings::toggleUp()
{
	if (this->currentChoice == 0) {
		this->currentChoice = this->maxChoice - 1;
	}
	else {
		this->currentChoice--;
	}
}

void CharacterSettings::toggleDown()
{
	this->currentChoice = (this->currentChoice + 1) % this->maxChoice;
}