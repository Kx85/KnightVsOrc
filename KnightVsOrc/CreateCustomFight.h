#pragma once
#include <vector>
#include <string>

#include "Abilities.h"
#include "Weapon.h"
#include "Character.h"
#include "Fight.h"
class CreateCustomFight
{
public:
	CreateCustomFight();
	~CreateCustomFight();

	std::string getTextToDisplay();
	std::string getTextToDisplay(Fight* f);

	void addChar(const char c);
	void removeChar();
	void nextMenu();
	void validate();

	const int getSelector();
	const bool hasSavedChar();
	void loadPlayer();
	bool hasMore();
	bool isReady();

	void start(Fight* f);
	void clear();
	void reset();

private:
	int currentMenu = 0;
	std::vector <std::string> menu;
	std::vector <std::string> answer;

	std::vector<Abilities> abilities;
	std::vector<Weapon> weapons;
	std::vector<Character> characters;

	std::vector<Character> charToFight;

	int currentSelector = 0;
	const int maxSelector = 5;

	int createdPlayer = 0;
	int currentRow = 0;
};

