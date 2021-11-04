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

void Abilities::setName(const std::string name)
{
	this->name = name;
}

const int Abilities::getDamage()
{
	return this->damage;
}

void Abilities::setDamage(const int damage)
{
	this->damage = damage;
}

const GeneralTypes::Status& Abilities::getInflictedStatus()
{
	return this->inflictedStatus;
}

void Abilities::setInflictedStatus(const GeneralTypes::Status& status)
{
	this->inflictedStatus = status;
}

const GeneralTypes::ModifierType& Abilities::getModifierType()
{
	return this->modifierType;
}

void Abilities::setModifierType(const GeneralTypes::ModifierType& modifierType)
{
	this->modifierType = modifierType;
}

const int Abilities::getModifier()
{
	return this->damageModifier;
}

void Abilities::setModifier(const int modifier)
{
	this->damageModifier = modifier;
}

const int Abilities::getCooldown()
{
	return this->cooldown;
}

void Abilities::setCooldown(const int cooldown)
{
	this->cooldown = cooldown;
	this->setBaseCooldown(cooldown);
}

const int Abilities::getAccuracy()
{
	return this->accuracy;
}

void Abilities::setAccuracy(const int accuracy)
{
	this->accuracy = accuracy;
}

const int Abilities::getEffectDuration()
{
	return this->effectDuration;
}

void Abilities::setEffectDuration(const int duration)
{
	this->effectDuration = duration;
}

bool Abilities::isSelfAbility()
{
	bool isSelf = false;

	switch (this->getInflictedStatus()) {
	case GeneralTypes::Status::Buff:
		isSelf = !isSelf;
		break;
	}

	return isSelf;
}

void Abilities::dcrCooldown()
{
	if (this->cooldown == 0)
		this->cooldown = this->baseCooldown;
	else
		this->cooldown--;
}

void Abilities::reset()
{
	this->cooldown = this->baseCooldown;
}

const bool Abilities::isReady()
{
	return (this->baseCooldown == this->cooldown) ? true : false;
}

const int Abilities::getBaseCooldown()
{
	return this->baseCooldown;
}

void Abilities::endTurn()
{
	(this->baseCooldown - this->cooldown) == 0 ? this->cooldown-- : NULL;
}

void Abilities::setBaseCooldown(const int baseCooldown)
{
	this->baseCooldown = baseCooldown;
}
