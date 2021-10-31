#pragma once
#include <string>

#include "GeneralTypes.h"
class Abilities
{
public:
	Abilities();
	Abilities(const Abilities& ability);
	Abilities(const std::string name,
		const GeneralTypes::Status inflictedStatus,
		const int damage,
		const int damageModifier,
		const GeneralTypes::ModifierType modifierType,
		const int cooldown,
		const int accuracy,
		const int effectDuration);
	~Abilities();

	const std::string getName();
	const int getDamage();
	const GeneralTypes::Status& getInflictedStatus();
	const GeneralTypes::ModifierType getModifierType();
	const int getModifier();
	const int getBaseCooldown();
	const int getCooldown();
	const int getAccuracy();
	const int getEffectDuration();

	void dcrCooldown();
	void reset();

	const bool isReady();

	void endTurn();

private:
	std::string name;
	int damage;
	int damageModifier;
	GeneralTypes::Status inflictedStatus;
	GeneralTypes::ModifierType modifierType;
	int cooldown;
	int baseCooldown;
	int accuracy;
	int effectDuration;
	int remainingEffectTurn;
};

