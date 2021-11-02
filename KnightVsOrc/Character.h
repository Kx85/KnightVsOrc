#pragma once
#include <string>
#include <vector>
#include "Weapon.h"
#include "GeneralTypes.h"
#include "Abilities.h"


class Character
{
public:
	Character();
	Character(const Character &c);
	Character(const GeneralTypes::Class type, const std::string name, const Weapon& weapon, const int shieldValue, const int health, const int team);
	~Character();

	const GeneralTypes::Class getType();
	void setType(const GeneralTypes::Class& type);

	const std::string getName();
	void setName(const std::string& name);

	const bool isPlayer();
	void togglePlayer();

	const int getShield();
	void setShield(const int v);

	const GeneralTypes::Status getStatus();
	void applyStatus(const GeneralTypes::Status& s, const int duration);

	const int getMaxHealth();
	void setMaxHealth(const int maxHealth);

	const int getMaxShield();
	void setMaxShield(const int maxShield); 

	const bool canAct();

	Weapon& getWeapon();
	void setWeapon(Weapon* weapon);

	Abilities& getAbility();
	void addAbility(Abilities* ability);

	void dcrCooldown();

	const int getHealth();
	void setHealth(const int health);
	void takeDamage(const int amount);
	void heal(const int amount);

	void reset();

	const std::string toString();

private:
	GeneralTypes::Class type;
	std::string name;
	bool player;
	int shieldValue;
	int maxShield;
	GeneralTypes::Status status;
	int health;
	int maxHealth;
	int team;
	Weapon weapon;
	Abilities abilitiesList;
	int statusDuration;
};

