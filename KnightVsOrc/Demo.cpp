#include <thread>
#include <string>
#include "Demo.h"
#include "Character.h"
#include "GeneralTypes.h"
#include "Fight.h"
#include "Weapon.h"
#include "Abilities.h"

Demo::Demo()
{
	this->started = false;
	this->paused = false;
	this->updated = false;
	this->updateInterval = 1000;
	this->players.clear();

	Character c1 = Character::Character(GeneralTypes::Class::Knight, "Knight", 50, 20, 1);
	Abilities a1 = Abilities("Charge",
		GeneralTypes::Status::NoStatus,
		0,
		2,
		GeneralTypes::ModifierType::Mult,
		3,
		60,
		0);
	Weapon w1 = Weapon("Sword", GeneralTypes::WeaponType::Sword, 5);
	c1.setWeapon(&w1);
	c1.setAbility(&a1);

	Character c2 = Character::Character(GeneralTypes::Class::Orc, "Orc", 0, 80, 2);
	Abilities a2 = Abilities("Stun",
		GeneralTypes::Status::Stunned,
		0,
		0,
		GeneralTypes::ModifierType::Add,
		5,
		20,
		1);
	Weapon w2 = Weapon("Axe", GeneralTypes::WeaponType::Axe, 8);
	c2.setWeapon(&w2);
	c2.setAbility(&a2);

	this->players.push_back(c1);
	this->players.push_back(c2);
}

const std::string Demo::getTextToDisplay(Fight* fight)
{
	return fight->displayRound();
}

void Demo::start(Fight* fight)
{
	fight->clear();
	for (unsigned int i = 0; i < this->players.size(); i++) {
		fight->addPlayer(this->players.at(i));
	}
	fight->start();

	while (!fight->hasEnded()) {
		fight->playDemoRound();
	}

}