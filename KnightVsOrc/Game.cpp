#include <Windows.h>
#include <stdio.h>
#include <iostream>

#include "Game.h"
#include "View.h"
#include "TitleScreen.h"
#include "ExitConfirmBox.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

Game::Game()
{
	
	View v = View::View();
	(this->v).operator=(v);
	this->lastKey = KEY_EVENT_RECORD();
	this->refresh = true;
}

Game::Game(View& v)
{
	(this->v).operator=(v);
	this->lastKey = KEY_EVENT_RECORD();
	this->refresh = true;
}

Game::~Game()
{
}

void Game::setView(View& v)
{
	(this->v).operator=(v);
}

View& Game::getView()
{
	return this->v;
}


void Game::start()
{
	this->update();

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	// Get the standard input handle.
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit.
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events.
	fdwMode = ENABLE_WINDOW_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");


	bool notOver = true;
	bool keyPressed = false;

	while (notOver) {

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler.

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
				//ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				//break;

			case FOCUS_EVENT:  // disregard focus events

			case MENU_EVENT:   // disregard menu events
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}

			switch (v.getContext()) {
			case GeneralTypes::ViewList::TitleScreen:
				processKeyTitleScreen();
				break;
			case GeneralTypes::ViewList::DemoExitConfirmBox:
				processKeyDemoExitConfirmBox();
				break;
			case GeneralTypes::ViewList::Demo:
				processKeyDemo();
				break;
			case GeneralTypes::ViewList::CreateCustomFight:
				processKeyCreateCustomFight();
				break;
			case GeneralTypes::ViewList::Fight:
				processKeyFight();
				break;
			case GeneralTypes::ViewList::FightConfirmBox:
				processKeyFightConfirmBox();
				break;
			case GeneralTypes::ViewList::SettingsModeWindow:
				processKeySettingsModeWindow();
				break;
			case GeneralTypes::ViewList::WeaponSettings:
				processKeyWeaponSettings();
				break;
			case GeneralTypes::ViewList::AbilitySettings:
				processKeyAbilitySettings();
				break;
			case GeneralTypes::ViewList::CharacterSettings:
				processKeyCharacterSettings();
				break;
			}
			
			this->update();
		}

	}
}

void Game::processKeyCharacterSettings() {
	switch (cSettings.getAction()) {
	case CharacterSettings::Action::Create:
		switch (lastKey.wVirtualKeyCode) {
		case VK_RETURN:
			if (cSettings.hasMore()) {
				cSettings.nextMenu(&customFight);
			}
			if (!cSettings.hasMore()) {
				cSettings.validate(&customFight);
				v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			}
			break;
		case VK_BACK:
			if (cSettings.getSelector() >= 0) {
				cSettings.removeChar();
			}
			if (cSettings.getSelector() < 0) {
				v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			}
			break;
		case VK_SHIFT:
		case VK_RSHIFT:
			break;
		default:
			if (lastKey.bKeyDown)
				cSettings.addChar(lastKey.uChar.AsciiChar);
			break;
		}
		break;
	case CharacterSettings::Action::Delete:
		switch (lastKey.wVirtualKeyCode) {
		case VK_BACK:
			v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			break;
		case VK_RETURN:
			if (cSettings.canDelete()) cSettings.deleteCharacter(&customFight);
			break;
		case VK_UP:
			cSettings.toggleUp();
			break;
		case VK_DOWN:
			cSettings.toggleDown();
			break;
		}
	}
}

void Game::processKeyAbilitySettings() {
	switch (aSettings.getAction()) {
	case AbilitySettings::Action::Create:
		switch (lastKey.wVirtualKeyCode) {
		case VK_RETURN:
			if (aSettings.hasMore()) {
				aSettings.nextMenu(&customFight);
			}
			if (!aSettings.hasMore()) {
				aSettings.validate(&customFight);
				v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			}
			break;
		case VK_BACK:
			if (aSettings.getSelector() >= 0) {
				aSettings.removeChar();
			}
			if (aSettings.getSelector() < 0) {
				v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			}
			break;
		case VK_SHIFT:
		case VK_RSHIFT:
			break;
		default:
			if (lastKey.bKeyDown)
				aSettings.addChar(lastKey.uChar.AsciiChar);
			break;
		}
		break;
	case AbilitySettings::Action::Delete:
		switch (lastKey.wVirtualKeyCode) {
		case VK_BACK:
			v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			break;
		case VK_RETURN:
			if (aSettings.canDelete()) aSettings.deleteAbility(&customFight);
			break;
		case VK_UP:
			aSettings.toggleUp();
			break;
		case VK_DOWN:
			aSettings.toggleDown();
			break;
		}
	}
}

void Game::processKeyWeaponSettings() {
	switch (wSettings.getAction()) {
	case WeaponSettings::Action::Create:
		switch (lastKey.wVirtualKeyCode) {
		case VK_RETURN:
			if (wSettings.hasMore()) {
				wSettings.nextMenu(&customFight);
			}
			if (!wSettings.hasMore()) {
				wSettings.validate(&customFight);
				v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			}
			break;
		case VK_BACK:
			if (wSettings.getSelector() >= 0) {
				wSettings.removeChar();
			}
			if (wSettings.getSelector() < 0) {
				v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			}
			break;
		case VK_SHIFT:
		case VK_RSHIFT:
			break;
		default:
			if (lastKey.bKeyDown)
				wSettings.addChar(lastKey.uChar.AsciiChar);
			break;
		}
		break;
	case WeaponSettings::Action::Delete:
		switch (lastKey.wVirtualKeyCode) {
		case VK_BACK:
			v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
			break;
		case VK_RETURN:
			if (wSettings.canDelete()) wSettings.deleteWeapon(&customFight);
			break;
		case VK_UP:
			wSettings.toggleUp();
			break;
		case VK_DOWN:
			wSettings.toggleDown();
			break;
		}
	}
}

void Game::processKeySettingsModeWindow() {
	switch (lastKey.wVirtualKeyCode) {
	case VK_RETURN:
		if (!settings.hasNextMenu()) {
			switch (settings.getLastSelected()) {
			case SettingsModeWindow::MenuOptions::Weapons:
				v.setContext(GeneralTypes::ViewList::WeaponSettings);
				wSettings.setAction(WeaponSettings::Action(settings.getChoice()));
				wSettings.reset(&customFight);
				break;
			case SettingsModeWindow::MenuOptions::Abilities:
				v.setContext(GeneralTypes::ViewList::AbilitySettings);
				aSettings.setAction(AbilitySettings::Action(settings.getChoice()));
				aSettings.reset(&customFight);
				break;
			case SettingsModeWindow::MenuOptions::Characters:
				v.setContext(GeneralTypes::ViewList::CharacterSettings);
				cSettings.setAction(CharacterSettings::Action(settings.getChoice()));
				cSettings.reset(&customFight);
				break;
			}
		}
		break;
	case VK_LEFT:
		settings.toggleLeftChoice();
		break;
	case VK_RIGHT:
		settings.toggleRightChoice();
		break;
	case VK_BACK:
		if (!settings.hasPreviousMenu()) {
			v.setContext(GeneralTypes::ViewList::TitleScreen);
		}
		break;
	}
}

void Game::processKeyFightConfirmBox() {
	switch (lastKey.wVirtualKeyCode) {
	case VK_RETURN:
		if (exitBox.getChoice() == 0) {
			v.setContext(GeneralTypes::ViewList::TitleScreen);
			std::cout << "Changing view to TitleScreen" << std::endl;
		}
		else if (exitBox.getChoice() == 1) {
			v.setContext(GeneralTypes::ViewList::Fight);
			customFight.start(&fight);
		}
	case VK_RIGHT:
	case VK_LEFT:
		exitBox.toggleChoice();
		break;
	}
}

void Game::processKeyFight() {
	if (lastKey.bKeyDown)
		v.setContext(GeneralTypes::ViewList::FightConfirmBox);
}

void Game::processKeyCreateCustomFight() {
	switch (lastKey.wVirtualKeyCode) {
	case VK_RETURN:
		if (customFight.hasMore()) {
			customFight.nextMenu();
		}
		if (!customFight.hasMore()) {
			customFight.validate();
		}
		if (customFight.isReady()) {
			customFight.start(&fight);
			v.setContext(GeneralTypes::ViewList::Fight);
		}
		break;
	case VK_BACK:
		if (customFight.getSelector() >= 0) {
			customFight.removeChar();
		}
		if (customFight.getSelector() < 0) {
			if (customFight.hasSavedChar())
				customFight.loadPlayer();
			else
				v.setContext(GeneralTypes::ViewList::TitleScreen);
		}
		break;
	case VK_SHIFT:
	case VK_RSHIFT:
			break;
	default:
		if (lastKey.bKeyDown)
			customFight.addChar(lastKey.uChar.AsciiChar);
		break;
	}
}

void Game::processKeyDemoExitConfirmBox() {
	switch (lastKey.wVirtualKeyCode) {
	case VK_RETURN:
		if (exitBox.getChoice() == 0) {
			v.setContext(GeneralTypes::ViewList::TitleScreen);
			std::cout << "Changing view to TitleScreen" << std::endl;
		}
		else if (exitBox.getChoice() == 1) {
			v.setContext(GeneralTypes::ViewList::Demo);
			demo.start(&fight);
			std::cout << "Changing view to Demo from confirm box" << std::endl;
		}
		break;
	case VK_RIGHT:
	case VK_LEFT:
		exitBox.toggleChoice();
		break;
	}
}

void Game::processKeyTitleScreen() {
	switch (lastKey.wVirtualKeyCode) {
	case VK_RETURN:
		if (ts.getChoice() == 0) {
			v.setContext(GeneralTypes::ViewList::CreateCustomFight);
			customFight.reset();
			std::cout << "Changing view to CreateCustomFight" << std::endl;
		}
		else if (ts.getChoice() == 1) {
			v.setContext(GeneralTypes::ViewList::Demo);
			demo.start(&fight);
			std::cout << "Changing view to Demo" << std::endl;
		}
		else if (ts.getChoice() == 2) {
			v.setContext(GeneralTypes::ViewList::SettingsModeWindow);
		}
		break;
	case VK_DOWN:
		ts.toggleDownChoice();
		break;
	case VK_UP:
		ts.toggleUpChoice();
		break;
	}
}

void Game::processKeyDemo()
{
	if (lastKey.bKeyDown)
		v.setContext(GeneralTypes::ViewList::DemoExitConfirmBox);
}

void Game::update()
{
	if (!this->refresh) return;

	GeneralTypes::ViewList vlist = v.getContext();
	switch (vlist) {
	case GeneralTypes::ViewList::TitleScreen:
		v.render(ts.getTextToDisplay());
		break;
	case GeneralTypes::ViewList::Demo:
		v.render(fbegin.getTextToDisplay(&fight));
		Sleep(3000);
		v.render(demo.getTextToDisplay(&fight));
		break;
	case GeneralTypes::ViewList::DemoExitConfirmBox:
		v.render(exitBox.getTextToDisplay());
		break;
	case GeneralTypes::ViewList::CreateCustomFight:
		v.render(customFight.getTextToDisplay());
		break;
	case GeneralTypes::ViewList::Fight:
		v.render(fbegin.getTextToDisplay(&fight));
		Sleep(3000);
		v.render(customFight.getTextToDisplay(&fight));
		break;
	case GeneralTypes::ViewList::FightConfirmBox:
		v.render(exitBox.getTextToDisplay());
		break;
	case GeneralTypes::ViewList::SettingsModeWindow:
		v.render(settings.getTextToDisplay());
		break;
	case GeneralTypes::ViewList::WeaponSettings:
		v.render(wSettings.getTextToDisplay());
		break;
	case GeneralTypes::ViewList::AbilitySettings:
		v.render(aSettings.getTextToDisplay());
		break;
	case GeneralTypes::ViewList::CharacterSettings:
		v.render(cSettings.getTextToDisplay());
		break;
	default:
		v.render(" ");
		break;
	}
	this->refresh = false;
}

void Game::setLastKey(const KEY_EVENT_RECORD& key)
{
	this->lastKey = key;
}

const KEY_EVENT_RECORD Game::getLastKey()
{
	return this->lastKey;
}

void Game::KeyEventProc(KEY_EVENT_RECORD ker)
{
	
	if (ker.bKeyDown && ker.wVirtualKeyCode != this->getLastKey().wVirtualKeyCode) {
		this->setLastKey(ker);
		this->refresh = true;
	}
	else if (!ker.bKeyDown) {
		this->setLastKey(KEY_EVENT_RECORD());
	}
}

void Game::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    //printf("Resize event\n");
    //printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
	std::cout << " " << std::endl;
}

void Game::ErrorExit(const char* lpszMessage)
{
	std::cerr << lpszMessage << std::endl;

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}