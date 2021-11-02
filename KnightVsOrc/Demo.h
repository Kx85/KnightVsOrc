#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <thread>
#include "Character.h"
#include "Fight.h"

class Demo
{
public:
	Demo();
	const std::string getTextToDisplay(Fight* f);
	void init();

	void start(Fight* f);

private:
	std::vector<Character> players;
	bool started;
	bool paused;
	bool updated;
	int updateInterval;

	void processDemo();
};

