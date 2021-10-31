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

	const bool hasStarted();
	const bool isUpdated();

	void start(Fight* f);
	void update();
	void pauseDemo();
	void resumeDemo();
	void endDemo();


private:
	std::vector<Character> players;
	bool started;
	bool paused;
	bool updated;
	int updateInterval;

	void processDemo();
};

