#include "Character.h"
#include "GeneralTypes.h"
#include <iostream>

Character::Character() {
	this->type = GeneralTypes::Class::Char;
	this->name = " ";
	this->player = false;
	this->shieldValue = 0;
	this->status = GeneralTypes::Status::NoStatus;
	this->health = 0;
	this->maxHealth = 0;
	this->team = 0;
}

Character::Character(const Character& c)
{
	type = c.type;
	name = c.name;
	player = c.player;
	shieldValue = c.shieldValue;
	status = c.status;
	maxHealth = c.maxHealth;
	health = c.maxHealth;
	team = c.team;
}

Character::Character(const GeneralTypes::Class type, const std::string name, const int shieldValue, const int maxHealth, const int team)
{
	Character();
	this->type = type;
	this->name = name;
	this->shieldValue = shieldValue;
	this->maxHealth = maxHealth;
	this->health = this->maxHealth;
	this->team = team;
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

void Character::applyStatus(const GeneralTypes::Status& s)
{
	this->status = s;
}

const int Character::getMaxHealth()
{
	return this->maxHealth;
}

void Character::setMaxHealth(const int& maxHealth)
{
	this->maxHealth = maxHealth;
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

void Character::toString()
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
}
