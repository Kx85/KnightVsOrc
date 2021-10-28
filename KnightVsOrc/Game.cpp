#include "Game.h"
#include "View.h"
#include <Windows.h>
#include <chrono>
#include <thread>

Game::Game()
{
	
	View v = View::View();
	(this->v).operator=(v);
}

Game::Game(View& v)
{
	(this->v).operator=(v);
}

Game::~Game()
{
}

void Game::setView(View& v)
{
	(this->v).operator=(v);
}

void Game::start()
{
	this->update();

	bool notOver = true;
	bool downPressed = false;
	while (notOver) {
		if ((GetKeyState('Q') & 0x8000)) {
			notOver = !notOver;
		}

		if ((GetKeyState(VK_DOWN) & 0x8000) && !downPressed) {
			downPressed = !downPressed;
			v.toggleChoice();
			this->update();
		}
		else if (!(GetKeyState(VK_DOWN) & 0x8000) && downPressed) {
			downPressed = !downPressed;
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

void Game::update()
{
	v.render();
}
