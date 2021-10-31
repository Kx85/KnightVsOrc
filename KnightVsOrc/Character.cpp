#include <iostream>
#include "Character.h"
#include "GeneralTypes.h"
#include "Weapon.h"
#include "Abilities.h"

Character::Character() {
	this->type = GeneralTypes::Class::Char;
	this->name = " ";
	this->player = false;
	this->shieldValue = 0;
	this->maxShield = 0;
	this->status = GeneralTypes::Status::NoStatus;
	this->health = 0;
	this->maxHealth = 0;
	this->team = 0;
	this->weapon = Weapon();
	this->abilitiesList	= Abilities();
	this->statusDuration = 0;
}

Character::Character(const Character& c)
{
	type = c.type;
	name = c.name;
	player = c.player;
	shieldValue = c.shieldValue;
	maxShield = c.maxShield;
	status = c.status;
	maxHealth = c.maxHealth;
	health = c.maxHealth;
	team = c.team;
	weapon = c.weapon;
	abilitiesList = c.abilitiesList;
	statusDuration = c.statusDuration;
}

Character::Character(const GeneralTypes::Class type, const std::string name, const Weapon& weapon, const int maxShield, const int maxHealth, const int team)
{
	
	this->type = type;
	this->name = name;
	this->maxShield = maxShield;
	this->shieldValue = this->maxShield;
	this->maxHealth = maxHealth;
	this->health = this->maxHealth;
	this->team = team;
	this->status = GeneralTypes::Status::NoStatus;
	this->player = false;
	this->weapon = weapon;
	abilitiesList = Abilities();
	this->statusDuration = 0;
}

Character::~Character() {}

const GeneralTypes::Class Character::getType() {
	return type;
}

void Character::setType(const GeneralTypes::Class& type) {
	this->type = type;
}

const std::string Character::getName()
{
	return name;
}

void Character::setName(const std::string& name)
{
	this->name = name;
}

const bool Character::isPlayer()
{
	return player;
}

void Character::togglePlayer()
{
	player = !player;
}

const int Character::getShield()
{
	return shieldValue;
}

void Character::setShield(const int v)
{
	this->shieldValue = v;
}

const GeneralTypes::Status Character::getStatus()
{
	return this->status;
}

void Character::applyStatus(const GeneralTypes::Status& s, const int duration)
{
	this->status = s;
	this->statusDuration = duration;
}

const int Character::getMaxHealth()
{
	return this->maxHealth;
}

void Character::setMaxHealth(const int maxHealth)
{
	this->maxHealth = maxHealth;
}

const int Character::getMaxShield()
{
	return this->maxShield;
}

void Character::setMaxShield(const int maxShield)
{
	this->maxShield = maxShield;
}

const bool Character::canAct()
{
	bool act = false;

	switch (this->status) {
	case GeneralTypes::Status::NoStatus:
		act = true;
		break;
	case GeneralTypes::Status::Stunned:
		act = false;
		break;
	}

	if (this->status != GeneralTypes::Status::NoStatus) {
		this->statusDuration--;

		if (this->statusDuration == 0) {
			this->status = GeneralTypes::Status::NoStatus;
		}
	}
	return act;
}

const Weapon& Character::getWeapon()
{
	return this->weapon;
}

void Character::setWeapon(const Weapon& weapon)
{
	this->weapon = weapon;
}

const Abilities& Character::getAbility()
{
	return this->abilitiesList;
}

void Character::addAbility(Abilities* ability)
{
	Abilities* a = ability;
	this->abilitiesList = *ability;
}

void Character::dcrCooldown()
{
	this->abilitiesList.dcrCooldown();
}

const int Character::getHealth()
{
	return this->health;
}

void Character::setHealth(const int health)
{
	this->health = health;
}

void Character::takeDamage(const int amount)
{
	int damage = amount;
	int hp = this->getHealth();
	int shield = this->getShield();

	if (shield > damage) {
		this->setShield(shield-damage);
		damage = 0;
	}
	else  {
		this->setShield(0);
		damage -= shield;
	}
	
	this->setHealth(hp - damage);

}

void Character::heal(const int amount)
{
	int hp = this->getHealth();
	int maxHp = this->getMaxHealth();

	int tmpHp = hp + amount;
	
	if (tmpHp >= maxHp) {
		this->setHealth(maxHp);
	}
	else {
		this->setHealth(tmpHp);
	}
}

void Character::reset()
{
	this->health = this->maxHealth;
	this->abilitiesList.reset();
}

const std::string Character::toString()
{
	
	std::cout << "The character is " << this->type << "class named " << this->name << "." << std::endl;
	std::cout << "This character uses no weapon, and has " 
		<< this->health << "/" 
		<< this->shieldValue 
		<< " (hp/shield)" 
		<< " fighting for team " 
		<< this->team 
		<< " (AI controlled : "
		<< GeneralTypes::BoolToString(this->player)
		<< ")."
		<< std::endl;

	return "The character is " + this->name + ".\n" + "This character uses no weapon, and has "
		+ std::to_string(this->health)
		+ "/"
		+ std::to_string(this->shieldValue)
		+ " (hp/shield).";
}
