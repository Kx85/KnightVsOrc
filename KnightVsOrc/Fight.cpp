#include <vector>

#include "Fight.h"
#include "GeneralTypes.h"
#include "Character.h"
#include "Weapon.h"
#include "Abilities.h"


Fight::Fight()
{
	Fight::clear();
}

Fight::~Fight()
{
}

void Fight::clear()
{
	this->players.clear();
	this->roundHistory.clear();
}

bool Fight::canStart()
{
	return true;
}

void Fight::start()
{
	this->matchOver = false;
	this->currentRound = 0;
	this->roundHistory.clear();

	for (int i = 0; i < this->players.size(); i++) {
		this->players.at(i).reset();
	}
}

void Fight::addPlayer(Character& c) {
	this->players.push_back(c);
}

const bool Fight::hasEnded()
{
	return this->matchOver;
}

bool hit(const int accuracy) {
	int roll = rand() % 100 + 1;
	return ((100 - accuracy) <= roll) ? true : false;
}

int processDamage(const int damage, Abilities* a) {
	int value = 0;
	switch (a->getModifierType()) {
	case GeneralTypes::ModifierType::Add:
		value = a->getDamage();
		break;
	case GeneralTypes::ModifierType::Mult:
		value = damage * a->getModifier() + a->getDamage();
		break;
	case GeneralTypes::ModifierType::PercentInc:
		value = a->getDamage() + damage * a->getModifier()/100;
		break;
	}

	switch (a->getInflictedStatus()) {
	case GeneralTypes::Status::Stunned:
		break;
	}

	return value;
}

void Fight::playDemoRound()
{
	std::string h = "Round " + std::to_string(++currentRound) + ":\n\n";;
	for (int i = 0; i < this->players.size(); i++) {
		Character* c1 = &this->players.at(i);
		Character* c2 = &this->players.at((i+1)%2);
		Weapon w1 = this->players.at(i).getWeapon();

		int damage = 0;
		if (c1->canAct()) {
			
				Abilities a = this->players.at(i).getAbility();
				if (a.isReady()) {
					if (hit(a.getAccuracy())) {
						damage = processDamage(w1.getDamage(), &a);
						c2->takeDamage(damage);

						h = h + c1->getName() + " used " + a.getName() + " and dealt " + std::to_string(damage) + " damage.\n";
						c2->applyStatus(a.getInflictedStatus(), a.getEffectDuration());
					}
					else {
						h = h + c1->getName() + " used " + a.getName() + " and missed!\n";
					}
				}
				else {
					damage = w1.getDamage();
					c2->takeDamage(damage);

					h = h + c1->getName() + " attacked " + c2->getName() + " with " + w1.getName() + " and dealt " + std::to_string(damage) + " damage.\n";
				}

				c1->dcrCooldown();
		}
		else {
			h = h + c1->getName() + " is stunned and can't move!\n";
		}

		h = h + c2->getName() + " has " + std::to_string(c2->getHealth()) + "/" + std::to_string(c2->getMaxHealth())
			+ " hp and " + std::to_string(c2->getShield()) + "/" + std::to_string(c2->getMaxShield()) + " shield.\n";
	}

	if (this->players.at(0).getHealth() <= 0 || this->players.at(1).getHealth() <= 0) {
		this->matchOver = !this->matchOver;
	}

	h = h + "\n--------------------------------\n";
	addHistory(h);
}

void Fight::addHistory(const std::string text)
{
	this->roundHistory.push_back({ text });
}

std::string Fight::displayRound()
{
	std::string toDisplay = "";

		for (int i = 0; i < roundHistory.size(); i++) {
			toDisplay = toDisplay + roundHistory.at(i);
		}

	return toDisplay;
}