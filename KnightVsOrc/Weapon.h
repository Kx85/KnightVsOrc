#pragma once
#include <string>
#include "GeneralTypes.h"
class Weapon
{
public:
	Weapon();
	Weapon(const std::string& name, const GeneralTypes::WeaponType& wtype, const int& damage);
	~Weapon();

	const std::string getName();
	void setName(const std::string name);

	const GeneralTypes::WeaponType getWeaponType();
	void setWeaponType(const GeneralTypes::WeaponType& wtype);

	const int getDamage();
	void setDamage(const int damage);

private:
	std::string name;
	GeneralTypes::WeaponType wtype;
	int damage;

};

