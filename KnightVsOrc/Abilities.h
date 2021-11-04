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
	void setName(const std::string name);
	const int getDamage();
	void setDamage(const int damage);
	const GeneralTypes::Status& getInflictedStatus();
	void setInflictedStatus(const GeneralTypes::Status& status);
	const GeneralTypes::ModifierType& getModifierType();
	void setModifierType(const GeneralTypes::ModifierType& type);
	const int getModifier();
	void setModifier(const int modifier);
	const int getBaseCooldown();
	const int getCooldown();
	void setCooldown(const int cooldown);
	const int getAccuracy();
	void setAccuracy(const int accuracy);
	const int getEffectDuration();
	void setEffectDuration(const int duration);

	bool isSelfAbility();
	void dcrCooldown();
	void reset();

	const bool isReady();

	void endTurn();

private:
	void setBaseCooldown(const int baseCooldown);

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

