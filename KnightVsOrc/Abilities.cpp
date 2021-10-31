#include "GeneralTypes.h"
#include "Abilities.h"

Abilities::Abilities()
{
	this->name = " ";
	this->damage = 0;
	this->inflictedStatus = GeneralTypes::Status::NoStatus;
	this->baseCooldown = -1;
	this->cooldown = 0;
	this->damageModifier = 0;
	this->modifierType = GeneralTypes::ModifierType::Add;
	this->accuracy = 100;
	this->effectDuration = 0;
}

Abilities::Abilities(const Abilities& ability)
{
	this->name = ability.name;
	this->damage = ability.damage;
	this->inflictedStatus = ability.inflictedStatus;
	this->baseCooldown = ability.baseCooldown;
	this->cooldown = ability.cooldown;
	this->damageModifier = ability.damageModifier;
	this->modifierType = ability.modifierType;
	this->accuracy = ability.accuracy;
	this->effectDuration = ability.effectDuration;
}

Abilities::Abilities(const std::string name,
	const GeneralTypes::Status inflictedStatus,
	const int damage,
	const int damageModifier,
	const GeneralTypes::ModifierType modifierType,
	const int cooldown,
	const int accuracy,
	const int effectDuration)
{
	this->name = name;
	this->damage = damage;
	this->inflictedStatus = inflictedStatus;
	this->baseCooldown = cooldown;
	this->cooldown = cooldown;
	this->damageModifier = damageModifier;
	this->modifierType = modifierType;
	this->accuracy = accuracy;
	this->effectDuration = effectDuration;
}

Abilities::~Abilities()
{
}

const std::string Abilities::getName()
{
	return this->name;
}

const int Abilities::getDamage()
{
	return this->damage;
}

const GeneralTypes::Status& Abilities::getInflictedStatus()
{
	return this->inflictedStatus;
}

const GeneralTypes::ModifierType Abilities::getModifierType()
{
	return this->modifierType;
}

const int Abilities::getModifier()
{
	return this->damageModifier;
}

const int Abilities::getCooldown()
{
	return this->cooldown;
}

const int Abilities::getAccuracy()
{
	return this->accuracy;
}

const int Abilities::getEffectDuration()
{
	return this->effectDuration;
}

void Abilities::dcrCooldown()
{
	this->cooldown = (this->cooldown - 1) % this->baseCooldown;
}

void Abilities::reset()
{
	this->cooldown = this->baseCooldown;
}

const bool Abilities::isReady()
{
	return ((this->baseCooldown - this->cooldown) == 0 ? true : false);
}

const int Abilities::getBaseCooldown()
{
	return this->baseCooldown;
}

void Abilities::endTurn()
{
	(this->baseCooldown - this->cooldown) == 0 ? this->cooldown-- : NULL;
}
