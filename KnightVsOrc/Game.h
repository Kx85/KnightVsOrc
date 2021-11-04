#pragma once
#include <windows.h>
#include <stdio.h>

#include "TitleScreen.h"
#include "Demo.h"
#include "ExitConfirmBox.h"
#include "View.h"
#include "Fight.h"
#include "FightBeginScreen.h"
#include "CreateCustomFight.h"
#include "SettingsModeWindow.h"
#include "WeaponSettings.h"
#include "AbilitySettings.h"
#include "CharacterSettings.h"
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

	void setLastKey(const KEY_EVENT_RECORD& key);
	const KEY_EVENT_RECORD getLastKey();


	void ErrorExit(const char*);
	void KeyEventProc(KEY_EVENT_RECORD);
	void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

private:
	void processKeyTitleScreen();
	void processKeyDemo();
	void processKeyDemoExitConfirmBox();
	void processKeyCreateCustomFight();
	void processKeyFight();
	void processKeyFightConfirmBox();
	void processKeySettingsModeWindow();
	void processKeyWeaponSettings();
	void processKeyAbilitySettings();
	void processKeyCharacterSettings();

	View v;
	KEY_EVENT_RECORD lastKey;
	bool refresh;
	TitleScreen ts = TitleScreen();
	ExitConfirmBox exitBox = ExitConfirmBox();
	Demo demo = Demo();
	Fight fight = Fight();
	FightBeginScreen fbegin = FightBeginScreen();
	CreateCustomFight customFight = CreateCustomFight();
	SettingsModeWindow settings = SettingsModeWindow();
	WeaponSettings wSettings = WeaponSettings();
	AbilitySettings aSettings = AbilitySettings();
	CharacterSettings cSettings = CharacterSettings();
};

