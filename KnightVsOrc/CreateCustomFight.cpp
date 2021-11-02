#include <map>
#include <string>
#include <regex>

#include "CreateCustomFight.h"

CreateCustomFight::CreateCustomFight()
{

	clear();
	this->charToFight.clear();
	this->abilities.push_back(Abilities("Charge",
		GeneralTypes::Status::NoStatus,
		0,
		2,
		GeneralTypes::ModifierType::Mult,
		3,
		60,
		0));
	this->abilities.push_back(Abilities("Stun",
		GeneralTypes::Status::Stunned,
		0,
		0,
		GeneralTypes::ModifierType::Add,
		5,
		20,
		1));

	this->weapons.push_back(Weapon("Sword", GeneralTypes::WeaponType::Sword, 5));
	this->weapons.push_back(Weapon("Axe", GeneralTypes::WeaponType::Axe, 8));
	Character c1 = Character::Character(GeneralTypes::Class::Knight, "Knight",
		this->weapons.at(0), 50, 20, 1);
	Abilities a1 = Abilities("Charge",
		GeneralTypes::Status::NoStatus,
		0,
		2,
		GeneralTypes::ModifierType::Mult,
		3,
		60,
		0);
	c1.addAbility(&a1);

	Character c2 = Character::Character(GeneralTypes::Class::Orc, "Orc",
		this->weapons.at(1), 0, 80, 2);
	Abilities a2 = Abilities("Stun",
		GeneralTypes::Status::Stunned,
		0,
		0,
		GeneralTypes::ModifierType::Add,
		5,
		20,
		1);
	c2.addAbility(&a2);
	this->characters.push_back(c1);
	this->characters.push_back(c2);
}

CreateCustomFight::~CreateCustomFight()
{
}

std::string CreateCustomFight::getTextToDisplay()
{
	int val = this->createdPlayer + 1;
	std::string text = "Player " + std::to_string(val) + "\n";

	for (int i = 0; i <= this->currentSelector; i++) {
		text = text + this->menu.at(i) + " " + this->answer.at(i) + "\n";
	}

	return text;
}

std::string CreateCustomFight::getTextToDisplay(Fight* f)
{
	return f->displayRound();
}

void CreateCustomFight::addChar(const char c)
{
	this->answer.at(currentSelector).push_back(c);
}

void CreateCustomFight::removeChar()
{
	if (this->answer.at(currentSelector).size() > 0)
		this->answer.at(currentSelector).pop_back();
	else
		currentSelector--;
}

void CreateCustomFight::nextMenu()
{
	bool validValue = false;
	switch (this->currentSelector) {
	case 0:
		if (std::regex_match(this->answer.at(currentSelector), std::regex("[a-zA-Z]+")))
			validValue = !validValue;
		break;
	case 1:
		for (int i = GeneralTypes::Class::Custom; i != GeneralTypes::Class::ClassCount; i++) {
			if (GeneralTypes::class_str[i] == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
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
		for (int i = 0; i < this->weapons.size(); i++) {
			if (this->weapons.at(i).getName() == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
		break;
	case 5:
		for (int i = 0; i < this->abilities.size(); i++) {
			if (this->abilities.at(i).getName() == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
		break;
	}

	if (this->currentSelector >= 0 && (this->answer.at(currentSelector) == "Orc" || this->answer.at(currentSelector) == "Knight")) {
		this->currentSelector = this->maxSelector;
	}

	if (validValue)
		this->currentSelector++;

}

void CreateCustomFight::validate()
{
	this->createdPlayer++;

	GeneralTypes::Class cl = GeneralTypes::Class::Custom;
	Character c = Character();
	int index = -1;

	for (int i = 0; i < this->characters.size(); i++) {
		if (this->characters.at(i).getName() == this->answer.at(0)) {
			cl = this->characters.at(i).getType();
			index = i;
			break;
		}
	}

	if (index == -1) {
		for (int i = GeneralTypes::Class::Custom; i != GeneralTypes::Class::ClassCount; i++) {
			for (int k = 0; k < this->characters.size(); k++) {
				if (GeneralTypes::class_str[this->characters.at(k).getType()] == this->answer.at(1)) {
					cl = this->characters.at(k).getType();
					index = k;
					break;
				}
			}
		}
	}

	switch (cl) {
	case GeneralTypes::Class::Knight:
	case GeneralTypes::Class::Orc:
		c = this->characters.at(index);
		c.setName(this->answer.at(0));
		break;
	case GeneralTypes::Class::Custom:
		c.setName(this->answer.at(0));
		c.setType(cl);
		c.setMaxHealth(std::stoi(this->answer.at(2)));
		c.setHealth(std::stoi(this->answer.at(2)));
		c.setMaxShield(std::stoi(this->answer.at(3)));
		c.setShield(std::stoi(this->answer.at(3)));

		for (int i = 0; i < this->weapons.size(); i++) {
			if (this->answer.at(4) == this->weapons.at(i).getName()) {
				c.setWeapon(&this->weapons.at(i));
			}
		}

		for (int i = 0; i < this->abilities.size(); i++) {
			if (this->answer.at(5) == this->abilities.at(i).getName()) {
				c.addAbility(&this->abilities.at(i));
			}
		}
		break;
	}

	this->charToFight.push_back(c);
	this->clear();
}

const int CreateCustomFight::getSelector()
{
	return this->currentSelector;
}

void CreateCustomFight::loadPlayer() {
	this->answer.at(0) = this->charToFight.at(createdPlayer).getName();
	this->answer.at(1) = GeneralTypes::class_str[this->charToFight.at(createdPlayer).getType()];
	this->answer.at(2) = std::to_string(this->charToFight.at(createdPlayer).getMaxHealth());
	this->answer.at(3) = std::to_string(this->charToFight.at(createdPlayer).getMaxShield());
	this->answer.at(4) = this->charToFight.at(createdPlayer).getWeapon().getName();
	this->answer.at(5) = this->charToFight.at(createdPlayer).getAbility().getName();
	this->charToFight.pop_back();
	this->currentSelector = this->maxSelector;
}

const bool CreateCustomFight::hasSavedChar()
{
	if (this->createdPlayer == 0)
		return false;
	else {
		createdPlayer--;
		return true;
	}
}

bool CreateCustomFight::hasMore()
{
	return (this->maxSelector - this->currentSelector) >= 0;
}

bool CreateCustomFight::isReady()
{
	return (this->createdPlayer == 2) ? true : false;
}

void CreateCustomFight::start(Fight* fight)
{
	fight->clear();
	for (int i = 0; i < this->charToFight.size(); i++) {
		fight->addPlayer(this->charToFight.at(i));
	}
	fight->start();


	while (!fight->hasEnded()) {
		fight->playDemoRound();
	}
}

std::string buildWeaponString(Weapon& w) {
	return w.getName() + " (" + std::to_string(w.getDamage()) + " damage), ";
}

void CreateCustomFight::clear()
{
	this->currentSelector = 0;
	this->menu.clear();
	this->answer.clear();

	std::string str = "Name (letter only): \n(Already available: ";
	for (int i = 0; i < this->characters.size(); i++) {
		str = str + this->characters.at(i).getName() + ", ";
	}
	str.pop_back();
	str.pop_back();
	menu.push_back(str + ")\n");
	answer.push_back("");

	str = "Type: (";
	for (int i = GeneralTypes::Class::Custom; i != GeneralTypes::Class::ClassCount; i++) {
		str = str + GeneralTypes::class_str[i] + ", ";
	}
	str.pop_back();
	str.pop_back();
	menu.push_back(str + ")\n");
	answer.push_back("");

	menu.push_back("Hp:");
	answer.push_back("");

	menu.push_back("Shield:");
	answer.push_back("");

	str = "Weapon: (";
	for (int i = 0; i < this->weapons.size(); i++) {
		str = str + buildWeaponString(this->weapons.at(i));// this->weapons.at(i).getName() + ", ";
	}
	str.pop_back();
	str.pop_back();
	menu.push_back(str + ")\n");
	answer.push_back("");

	str = "Ability: (";
	for (int i = 0; i < this->abilities.size(); i++) {
		str = str + this->abilities.at(i).getName() + ", ";
	}
	str.pop_back();
	str.pop_back();
	menu.push_back(str + ")\n");
	answer.push_back("");

	//placeholder
	menu.push_back("");
	answer.push_back("");
}


void CreateCustomFight::reset() {
	this->clear();
	this->charToFight.clear();
	this->createdPlayer = 0;
}