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
	const bool hasEnded();

	void playDemoRound();
	void addHistory(const std::string text);
	std::string displayRound();

private:
	std::vector<Character> players;
	std::vector<std::string> roundHistory;
	int currentRound;
	bool matchOver;

};

