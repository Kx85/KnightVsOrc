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

	Character c1 = Character::Character(GeneralTypes::Class::Knight, "Knight",
		Weapon("Sword", GeneralTypes::WeaponType::Sword, 5), 50, 20, 1);
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
		Weapon("Axe", GeneralTypes::WeaponType::Axe, 8), 0, 80, 2);
	Abilities a2 = Abilities("Stun",
		GeneralTypes::Status::Stunned,
		0,
		0,
		GeneralTypes::ModifierType::Add,
		5,
		20,
		1);
	c2.addAbility(&a2);

	this->players.push_back(c1);
	this->players.push_back(c2);
}

void Demo::init() {
}

const std::string Demo::getTextToDisplay(Fight* fight)
{
	return fight->displayRound();
}

void Demo::start(Fight* fight)
{
	this->init();
	fight->clear();
	for (int i = 0; i < this->players.size(); i++) {
		fight->addPlayer(this->players.at(i));
	}
	fight->start();

	while (!fight->hasEnded()) {
		fight->playDemoRound();
	}

}