#include <regex>

#include "WeaponSettings.h"
#include "GeneralTypes.h"

WeaponSettings::WeaponSettings()
{
	this->action = WeaponSettings::Action::Create;
}

WeaponSettings::~WeaponSettings()
{
}

std::string WeaponSettings::getTextToDisplay()
{
	std::string text = "";
	switch (this->action) {
	case Action::Create:
		for (int i = 0; i <= this->currentSelector; i++) {
			text = text + "\n" + this->menu.at(i) + " " + this->answer.at(i);
		}

		break;
	case Action::Delete:
		std::vector<std::string> tmpStrings = std::vector<std::string>(maxWeaponCount, baseString);

		std::size_t found = (size_t)50;

		// 2 first weapons can't be deleted
		tmpStrings.at(0).replace((size_t)5 + this->nameList.at(0).size(),
			14,
			"(Not erasable)");
		tmpStrings.at(1).replace((size_t)7 + this->nameList.at(1).size(),
			14,
			"(Not erasable)");

		// Display Weapon infos
		tmpStrings.at(1).replace(found + 5,
			this->weaponDescList.at(this->currentChoice).at(0).size(),
			this->weaponDescList.at(this->currentChoice).at(0));
		tmpStrings.at(2).replace(found + 5,
			this->weaponDescList.at(this->currentChoice).at(1).size(),
			this->weaponDescList.at(this->currentChoice).at(1));
		tmpStrings.at(3).replace(found + 5,
			this->weaponDescList.at(this->currentChoice).at(2).size(),
			this->weaponDescList.at(this->currentChoice).at(2));


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

		for (int i = this->maxChoice; i < maxWeaponCount; i++) {
			text = text + "\n" + tmpStrings.at(i);
		}
		break;
	}

	return text + this->error;
}

void WeaponSettings::addChar(char c)
{
	this->answer.at(currentSelector).push_back(c);
}

void WeaponSettings::removeChar()
{
	if (this->answer.at(currentSelector).size() > 0)
		this->answer.at(currentSelector).pop_back();
	else
		currentSelector--;
}

bool WeaponSettings::hasMore()
{
	return (this->maxSelector - this->currentSelector) >= 0;
}

void WeaponSettings::nextMenu(CreateCustomFight* f)
{
	bool validValue = false;
	error = "";
	switch (this->currentSelector) {
	case 0:
		validValue = !validValue;
		for (int i = 0; i < f->getWeaponsSize(); i++) {
			if (f->getWeapons()->at(i).getName() == this->answer.at(currentSelector)) {
				error = "(Weapon name already existing!)";
				validValue = !validValue;
				break;
			}
		}
		if (std::regex_match(this->answer.at(currentSelector), std::regex("[a-z][A-Z]+"))) {
			error = "(No empty name!)";
			validValue = !validValue;
		}
		break;
	case 1:
		for (int i = GeneralTypes::WeaponType::Fist; i != GeneralTypes::WeaponType::WeaponTypeCount; i++) {
			if (GeneralTypes::weaponType_str[i] == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
		break;
	case 2:
		if (std::regex_match(this->answer.at(currentSelector), std::regex("[1-9][0-9]*")))
			validValue = !validValue;
		break;
	}

	if (validValue)
		this->currentSelector++;
}

void WeaponSettings::validate(CreateCustomFight* f)
{
	GeneralTypes::WeaponType cl = GeneralTypes::WeaponType::Fist;
	Weapon w = Weapon();

	w.setName(this->answer.at(0));

	for (int i = GeneralTypes::WeaponType::Fist; i != GeneralTypes::WeaponType::WeaponTypeCount; i++) {
		if (GeneralTypes::weaponType_str[i] == this->answer.at(1)) {
			cl = static_cast<GeneralTypes::WeaponType>(i);
			break;
		}
	}

	w.setWeaponType(cl);
	w.setDamage(std::stoi(this->answer.at(2)));

	f->getWeapons()->push_back(w);
	
}

void WeaponSettings::setAction(WeaponSettings::Action a)
{
	this->action = a;
}

const WeaponSettings::Action WeaponSettings::getAction()
{
	return this->action;
}

const int WeaponSettings::getSelector()
{
	return this->currentSelector;
}

void WeaponSettings::reset(CreateCustomFight* f)
{
	std::string str = "";

	switch (this->action) {
	case Action::Create:
		this->currentSelector = 0;
		this->menu.clear();
		this->answer.clear();

		this->menu.push_back("Name:");
		this->answer.push_back("");

		str = "Type: (";
		for (int i = GeneralTypes::WeaponType::Sword; i != GeneralTypes::WeaponType::WeaponTypeCount; i++) {
			str = str + GeneralTypes::weaponType_str[i] + ", ";
		}
		str.pop_back();
		str.pop_back();
		this->menu.push_back(str + ")\n");
		this->answer.push_back("");

		this->menu.push_back("Damage:");
		this->answer.push_back("");
		break;
	case Action::Delete:
		this->nameList.clear();
		this->weaponDescList.clear();
		this->currentChoice = 0;
		this->maxChoice = f->getWeaponsSize();

		for (int i = 0; i < f->getWeaponsSize(); i++) {
			std::vector<std::string> descList;
			Weapon w = f->getWeapons()->at(i);

			std::string wType = GeneralTypes::weaponType_str[w.getWeaponType()];
			this->nameList.push_back(w.getName());
			descList.push_back("Name   : " + w.getName());
			descList.push_back("Type   : " + wType);
			descList.push_back("Damage : " + std::to_string(w.getDamage()));
			this->weaponDescList.push_back(descList);
		}
	}
}

bool WeaponSettings::canDelete()
{
	return (this->currentChoice > 1) ? true : false;
}

void WeaponSettings::deleteWeapon(CreateCustomFight* f)
{
	auto it = f->getWeapons()->begin() + this->currentChoice;
	f->getWeapons()->erase(it);
	this->reset(f);
}

void WeaponSettings::toggleUp()
{
	if (this->currentChoice == 0) {
		this->currentChoice = this->maxChoice - 1;
	}
	else {
		this->currentChoice--;
	}
}

void WeaponSettings::toggleDown()
{
	this->currentChoice = (this->currentChoice + 1) % this->maxChoice;
}
