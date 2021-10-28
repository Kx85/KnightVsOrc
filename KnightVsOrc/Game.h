#pragma once
#include "View.h"
class Game
{
public:
	Game();
	Game(View& v);
	~Game();

	void setView(View& v);
	void start();
	void update();

private:
	View v;
};

