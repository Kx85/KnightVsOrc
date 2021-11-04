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
		this->getPlayer(i)->reset();
	}

	if (this->getPlayer(0)->getWeapon().getSpeed() > this->getPlayer(1)->getWeapon().getSpeed()) {
		addHistory(this->getPlayer(0)->getName() + " is faster and will start first\n\n");
	}
	else if (this->getPlayer(0)->getWeapon().getSpeed() < this->getPlayer(1)->getWeapon().getSpeed()) {
		addHistory(this->getPlayer(1)->getName() + " is faster and will start first\n\n");
	}
	else {
		addHistory("Fighters are as fast as each others but default will be on player 1\n\n");
	}
}

void Fight::addPlayer(Character& c) {
	this->players.push_back(c);
}

Character* Fight::getPlayer(const int index)
{
	return &this->players.at(index);
}

const bool Fight::hasEnded()
{
	return this->matchOver;
}

bool hit(const int accuracy) {
	int roll = rand() % 100 + 1;
	return ((100 - accuracy) <= roll) ? true : false;
}

int processDamage(Character* c1, bool hitAbility, bool missed) {
	int value = 0;

	if (missed)
		return 0;

	if (hitAbility) {
		switch (c1->getAbility().getModifierType()) {
		case GeneralTypes::ModifierType::Add:
			value = c1->getAbility().getDamage();
			break;
		case GeneralTypes::ModifierType::Mult:
			value = c1->getWeapon().getDamage() * c1->getAbility().getModifier();
			break;
		}
	}
	else {
		switch (c1->getStatus()) {
		case GeneralTypes::Status::Buff:
			if (c1->getAbility().getModifierType() == GeneralTypes::ModifierType::PercentInc) {
				value = (int)std::ceil((c1->getWeapon().getDamage() * c1->getAbility().getModifier() / 100));
			}
			break;
		default:
			value = c1->getWeapon().getDamage();
		}
	}
	return value;
}

std::string Fight::processAttackAndGetResult(Character* c1, Character* c2, const bool canEnd) {
	int damage = 0;
	std::string h = "";
	if (hasEnded()) {
		return "";
	}

	if (c1->canAct()) {
		Weapon w1 = c1->getWeapon();
		Abilities a = c1->getAbility();
		bool hitAbility = false;
		bool missed = false;

		if (a.isReady()) {
			hitAbility = !hitAbility;
			if (hit(a.getAccuracy())) {
				if (a.isSelfAbility()) {
					c1->applyStatus(a.getInflictedStatus(), a.getEffectDuration());
				}
				else {
					c2->applyStatus(a.getInflictedStatus(), a.getEffectDuration());
				}
			}
			else {
				missed = !missed;
				h = h + c1->getName() + " used " + a.getName() + " and missed!\n";
			}
		} 
			damage = processDamage(c1, hitAbility, missed);

			if (hitAbility && !missed) {
				h = h + c1->getName() + " used " + a.getName() + " and dealt " + std::to_string(damage) + " damage.\n";
			}
			else if (!missed) {
				h = h + c1->getName() + " attacked " + c2->getName() + " with " + w1.getName() + " and dealt " + std::to_string(damage) + " damage.\n";
			}
		
		c2->takeDamage(damage);
		c1->dcrCooldown();
	}
	else {
		h = h + c1->getName() + " is stunned and can't move!\n";
	}

	h = h + c2->getName() + " has " + std::to_string(c2->getHealth()) + "/" + std::to_string(c2->getMaxHealth())
		+ " hp and " + std::to_string(c2->getShield()) + "/" + std::to_string(c2->getMaxShield()) + " shield.\n";

	if (!canEnd)
		return h;

	if (c1->getHealth() <= 0 || c2->getHealth() <= 0) {
		this->matchOver = !this->matchOver;

		if (c1->getHealth() <= 0 && c2->getHealth() > 0)
			h = h + "\n" + c2->getName() + " won the fight!\n";
		else if (c2->getHealth() <= 0 && c1->getHealth() > 0)
			h = h + "\n" + c1->getName() + " won the fight!\n";
		else
			h = h + "\nFight ends with a draw";
	}

	return h;
}

void Fight::playDemoRound()
{
	std::string h = "Round " + std::to_string(++currentRound) + ":\n\n";;
	Character* c1 = this->getPlayer(0);
	Character* c2 = this->getPlayer(1);

	if (c1->getWeapon().getSpeed() > c2->getWeapon().getSpeed()) {
		h = h + processAttackAndGetResult(c1, c2, true);
		h = h + processAttackAndGetResult(c2, c1, true);
	}
	else if (c1->getWeapon().getSpeed() < c2->getWeapon().getSpeed()) {
		h = h + processAttackAndGetResult(c2, c1, true);
		h = h + processAttackAndGetResult(c1, c2, true);
	}

	if (c1->getWeapon().getSpeed() == c2->getWeapon().getSpeed()) {
		h = h + processAttackAndGetResult(c1, c2, false);
		h = h + processAttackAndGetResult(c2, c1, true);
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