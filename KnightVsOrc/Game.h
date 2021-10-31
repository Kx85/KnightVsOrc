#pragma once
#include <windows.h>
#include <stdio.h>

#include "TitleScreen.h"
#include "Demo.h"
#include "DemoExitConfirmBox.h"
#include "View.h"
#include "Fight.h"
class Game
{
public:
	Game();
	Game(View& v);
	~Game();

	void setView(View& v);
	View& getView();

	void start();
	void update();

	void setLastKey(const short& key);
	const short getLastKey();

	void processKeyTitleScreen();
	void processKeyDemo();
	void processKeyDemoExitConfirmBox();
	void processKey();

	void ErrorExit(const char*);
	void KeyEventProc(KEY_EVENT_RECORD);
	void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

private:
	View v;
	short lastKey;
	TitleScreen ts = TitleScreen();
	DemoExitConfirmBox demoExit = DemoExitConfirmBox();
	Demo demo = Demo();
	Fight fight = Fight();
};

