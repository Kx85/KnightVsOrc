#include "Weapon.h"
Weapon::Weapon() {
	this->name = " ";
	this->wtype = GeneralTypes::WeaponType::Fist;
	this->damage = 0;
	this->speed = 0;
}

Weapon::Weapon(const std::string& name, const GeneralTypes::WeaponType& wtype, const int& damage)
{
	this->name = name;
	this->wtype = wtype;
	this->damage = damage;
	switch (wtype) {
	case GeneralTypes::WeaponType::Sword:
		this->speed = 60;
		break;
	case GeneralTypes::WeaponType::Axe:
		this->speed = 40;
		break;
	}
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
	switch (wtype) {
	case GeneralTypes::WeaponType::Sword:
		this->speed = 60;
		break;
	case GeneralTypes::WeaponType::Axe:
		this->speed = 40;
		break;
	}
}

const int Weapon::getDamage()
{
	return this->damage;
}

void Weapon::setDamage(const int damage)
{
	this->damage = damage;
}

const int Weapon::getSpeed()
{
	return this->speed;
}
