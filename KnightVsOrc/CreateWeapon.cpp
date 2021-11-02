#include <regex>

#include "CreateWeapon.h"
#include "GeneralTypes.h"

CreateWeapon::CreateWeapon()
{
	this->reset();
}

CreateWeapon::~CreateWeapon()
{
}

std::string CreateWeapon::getTextToDisplay()
{
	std::string text = "\n";

	for (int i = 0; i <= this->currentSelector; i++) {
		text = text + this->menu.at(i) + " " + this->answer.at(i) + "\n";
	}
	
	return text + this->error;
}

void CreateWeapon::addChar(char c)
{
	this->answer.at(currentSelector).push_back(c);
}

void CreateWeapon::removeChar()
{
	if (this->answer.at(currentSelector).size() > 0)
		this->answer.at(currentSelector).pop_back();
	else
		currentSelector--;
}

bool CreateWeapon::hasMore()
{
	return (this->maxSelector - this->currentSelector) >= 0;
}

void CreateWeapon::nextMenu(CreateCustomFight* f)
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

	if (this->currentSelector >= 0 && (this->answer.at(currentSelector) == "Orc" || this->answer.at(currentSelector) == "Knight")) {
		this->currentSelector = this->maxSelector;
	}

	if (validValue)
		this->currentSelector++;
}

void CreateWeapon::validate(CreateCustomFight* f)
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

const int CreateWeapon::getSelector()
{
	return this->currentSelector;
}

void CreateWeapon::reset()
{
	std::string str = "";

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
}
