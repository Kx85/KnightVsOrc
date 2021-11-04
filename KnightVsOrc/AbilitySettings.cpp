#include <regex>

#include "AbilitySettings.h"
#include "GeneralTypes.h"

AbilitySettings::AbilitySettings()
{
	this->action = AbilitySettings::Action::Create;
}

AbilitySettings::~AbilitySettings()
{
}

std::string AbilitySettings::getTextToDisplay()
{
	std::string text = "";
	switch (this->action) {
	case Action::Create:
		for (int i = 0; i <= this->currentSelector; i++) {
			text = text + "\n" + this->menu.at(i) + " " + this->answer.at(i);
		}

		break;
	case Action::Delete:
		std::vector<std::string> tmpStrings = std::vector<std::string>(maxAbilityCount, baseString);

		std::size_t found = (size_t)50;

		// 2 first abilities can't be deleted
		tmpStrings.at(0).replace((size_t)5 + this->nameList.at(0).size(),
			14,
			"(Not erasable)");
		tmpStrings.at(1).replace((size_t)7 + this->nameList.at(1).size(),
			14,
			"(Not erasable)");

		// Display Ability infos
		for (int i = 0; i < 8; i++) {
			tmpStrings.at(i+1).replace(found + 5,
				this->abilityDescList.at(this->currentChoice).at(i).size(),
				this->abilityDescList.at(this->currentChoice).at(i));
		}

		for (int i = 0; i < this->maxChoice; i++) {
			int length = ((int)this->nameList.at(i).size() < 45) ? (int)this->nameList.at(i).size() : 45;

			if (i == this->currentChoice) {
				tmpStrings.at(i).replace(1, 2, "->");
				tmpStrings.at(i).replace(3, length, this->nameList.at(i));
				tmpStrings.at(i).replace((size_t)3 + length, 2, "<-");
			}
			else {
				tmpStrings.at(i).replace(3, length, this->nameList.at(i));
			}
			text = text + "\n" + tmpStrings.at(i);
		}

		for (int i = this->maxChoice; i < maxAbilityCount; i++) {
			text = text + "\n" + tmpStrings.at(i);
		}
		break;
	}

	return text + this->error;
}

void AbilitySettings::addChar(char c)
{
	this->answer.at(currentSelector).push_back(c);
}

void AbilitySettings::removeChar()
{
	if (this->answer.at(currentSelector).size() > 0)
		this->answer.at(currentSelector).pop_back();
	else
		currentSelector--;
}

bool AbilitySettings::hasMore()
{
	return (this->maxSelector - this->currentSelector) >= 0;
}

void AbilitySettings::nextMenu(CreateCustomFight* f)
{
	bool validValue = false;
	error = "";
	switch (this->currentSelector) {
	case 0:
		validValue = !validValue;
		for (int i = 0; i < f->getAbilitiesSize(); i++) {
			if (f->getAbilities()->at(i).getName() == this->answer.at(currentSelector)) {
				error = "\n(Ability name already existing!)\n";
				validValue = !validValue;
				break;
			}
		}
		if (!std::regex_match(this->answer.at(currentSelector), std::regex("[a-zA-Z]+"))) {
			error = "\n(Only letters!)\n";
			validValue = !validValue;
		}
		break;
	case 1:
		for (int i = GeneralTypes::Status::NoStatus; i != GeneralTypes::Status::StatusCount; i++) {
			if (GeneralTypes::status_str[i] == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
		if (!validValue)
			error = "\n(Wrong status entered!)\n";
		break;
	case 2:
	case 4:
		if (std::regex_match(this->answer.at(currentSelector), std::regex("[0-9]+")))
			validValue = !validValue;
		break;
	case 5:
	case 6:
	case 7:
		if (std::regex_match(this->answer.at(currentSelector), std::regex("[1-9][0-9]*")))
			validValue = !validValue;
		break;
	case 3:
		for (int i = GeneralTypes::ModifierType::Add; i != GeneralTypes::ModifierType::ModifierTypeCount; i++) {
			if (GeneralTypes::modifierType_str[i] == this->answer.at(currentSelector)) {
				validValue = !validValue;
				break;
			}
		}
		if (!validValue)
			error = "\n(Wrong Modifier entered!)\n";
		break;
	}

	if (validValue)
		this->currentSelector++;
}

void AbilitySettings::validate(CreateCustomFight* f)
{
	GeneralTypes::Status status;
	GeneralTypes::ModifierType type;
	Abilities a = Abilities();

	a.setName(this->answer.at(0));

	for (int i = GeneralTypes::Status::NoStatus; i != GeneralTypes::Status::StatusCount; i++) {
		if (GeneralTypes::status_str[i] == this->answer.at(1)) {
			status = static_cast<GeneralTypes::Status>(i);
			break;
		}
	}

	a.setInflictedStatus(status);
	a.setDamage(std::stoi(this->answer.at(2)));

	int index;
	for (int i = GeneralTypes::ModifierType::Add; i != GeneralTypes::ModifierType::ModifierTypeCount; i++) {
		if (GeneralTypes::modifierType_str[i] == this->answer.at(3)) {
			type = static_cast<GeneralTypes::ModifierType>(i);
			index = i;
			break;
		}
	}

	a.setModifierType(type);
	a.setModifier(std::stoi(this->answer.at(4)));
	a.setCooldown(std::stoi(this->answer.at(5)));
	a.setAccuracy(std::stoi(this->answer.at(6)));
	a.setEffectDuration(std::stoi(this->answer.at(7)));

	f->getAbilities()->push_back(a);

}

void AbilitySettings::setAction(AbilitySettings::Action a)
{
	this->action = a;
}

const AbilitySettings::Action AbilitySettings::getAction()
{
	return this->action;
}

const int AbilitySettings::getSelector()
{
	return this->currentSelector;
}

void AbilitySettings::reset(CreateCustomFight* f)
{
	std::string str = "";

	switch (this->action) {
	case Action::Create:
		this->currentSelector = 0;
		this->menu.clear();
		this->answer.clear();

		this->menu.push_back("Name:");
		this->answer.push_back("");

		str = "Inflicted Status: (";
		for (int i = GeneralTypes::Status::NoStatus; i != GeneralTypes::Status::StatusCount; i++) {
			str = str + GeneralTypes::status_str[i] + ", ";
		}
		str.pop_back();
		str.pop_back();
		this->menu.push_back(str + ")\n");
		this->answer.push_back("");

		this->menu.push_back("Damage:");
		this->answer.push_back("");


		str = "Damage Modifier Type: (";
		for (int i = GeneralTypes::ModifierType::Add; i != GeneralTypes::ModifierType::ModifierTypeCount; i++) {
			str = str + GeneralTypes::modifierType_str[i] + ", ";
		}
		str.pop_back();
		str.pop_back();
		this->menu.push_back(str + ")\n");
		this->answer.push_back("");


		this->menu.push_back("Damage Modifier Value:");
		this->answer.push_back("");

		this->menu.push_back("Cooldown:");
		this->answer.push_back("");

		this->menu.push_back("Accuracy:");
		this->answer.push_back("");

		this->menu.push_back("Effect Duration:");
		this->answer.push_back("");
		break;
	case Action::Delete:
		this->nameList.clear();
		this->abilityDescList.clear();
		this->currentChoice = 0;
		this->maxChoice = f->getAbilitiesSize();

		for (int i = 0; i < f->getAbilitiesSize(); i++) {
			std::vector<std::string> descList;
			Abilities a = f->getAbilities()->at(i);
			std::string inflicted = GeneralTypes::status_str[a.getInflictedStatus()];
			std::string aType = GeneralTypes::modifierType_str[a.getModifierType()];

			this->nameList.push_back(a.getName());
			descList.push_back("Name            : " + a.getName());
			descList.push_back("Inflicted Status: " + inflicted);
			descList.push_back("Damage          : " + std::to_string(a.getDamage()));
			descList.push_back("Type            : " + aType);
			switch (a.getModifierType()) {
			case GeneralTypes::ModifierType::Add:
			case GeneralTypes::ModifierType::Mult:
				descList.push_back("Damage Modifier : " + std::to_string(a.getModifier()));
				break;
			case GeneralTypes::ModifierType::PercentInc:
				descList.push_back("Damage Modifier : " + std::to_string(a.getModifier()) + "%");
				break;
			}
			descList.push_back("Cooldown        : " + std::to_string(a.getCooldown()));
			descList.push_back("Accuracy        : " + std::to_string(a.getAccuracy()));
			descList.push_back("Effect duration : " + std::to_string(a.getEffectDuration()));
			this->abilityDescList.push_back(descList);
		}
	}
}

bool AbilitySettings::canDelete()
{
	return (this->currentChoice > 1) ? true : false;
}

void AbilitySettings::deleteAbility(CreateCustomFight* f)
{
	auto it = f->getAbilities()->begin() + this->currentChoice;
	f->getAbilities()->erase(it);
	this->reset(f);
}

void AbilitySettings::toggleUp()
{
	if (this->currentChoice == 0) {
		this->currentChoice = this->maxChoice - 1;
	}
	else {
		this->currentChoice--;
	}
}

void AbilitySettings::toggleDown()
{
	this->currentChoice = (this->currentChoice + 1) % this->maxChoice;
}