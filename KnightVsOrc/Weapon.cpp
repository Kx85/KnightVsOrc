#include "Weapon.h"
Weapon::Weapon() {
	this->name = " ";
	this->wtype = GeneralTypes::WeaponType::Fist;
	this->damage = 0;
}

Weapon::Weapon(const std::string& name, const GeneralTypes::WeaponType& wtype, const int& damage)
{
	this->name = name;
	this->wtype = wtype;
	this->damage = damage;
}

Weapon::~Weapon()
{
}

const std::string Weapon::getName()
{
	return this->name;
}

void Weapon::setName(const std::string name)
{
	this->name = name;
}

const GeneralTypes::WeaponType Weapon::getWeaponType()
{
	return this->wtype;
}

void Weapon::setWeaponType(const GeneralTypes::WeaponType& wtype)
{
	this->wtype = wtype;
}

const int Weapon::getDamage()
{
	return this->damage;
}

void Weapon::setDamage(const int damage)
{
	this->damage = damage;
}
