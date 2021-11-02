#pragma once
#include <vector>
#include <string>
#include <map>
#include "Character.h"

class Fight
{
public:
	Fight();
	~Fight();

	void clear();

	bool canStart();
	void start();

	void addPlayer(Character& c);
	Character* getPlayer(const int index);
	const bool hasEnded();

	void playDemoRound();
	void addHistory(const std::string text);
	std::string displayRound();

private:
	std::string processAttackAndGetResult(Character* c1, Character* c2, const bool canEnd);

	std::vector<Character> players;
	std::vector<std::string> roundHistory;
	int currentRound;
	bool matchOver;
};

