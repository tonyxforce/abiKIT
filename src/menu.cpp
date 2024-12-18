#include "gameEngine.h"
#include "menu.h"
#include "settings.h"

void menuSetup() {

};

int selectedOption = 0;

enum MenuType
{
	menutype_CHECKBOX,
	menutype_NUMBER,
	menutype_MENU,
	menutype_BUTTON,
};

const int gameMenuLen = 3;

enum GameMenuOption
{
	gamemenuoption_PONG,
	gamemenuoption_SNAKE,
	gamemenuoption_SETTINGS,
};

String gameMenuOptionsStrings[gameMenuLen] = {
		"Pong",
		"Snake",
		"Beallitasok"};

const int settingsMenuLen = 3;
enum SettingsMenuOption
{
	settingsmenuoption_SOUNDS,
	settingsmenuoption_DEBUGMODE,
	settingsmenuoption_BACK,
};

String settingsMenuOptionsStrings[settingsMenuLen] = {
		"Hang ki/be",
		"Debug mod ki/be",
		"Vissza",
};

MenuType settingsMenuOptionsTypes[] = {
		menutype_CHECKBOX,
		menutype_CHECKBOX,
		menutype_BUTTON,
		menutype_BUTTON};

bool *changeableOptions[settingsMenuLen] = {
		&settings.debugMode,
		&settings.soundEnabled,
		nullptr,
};

enum Menu
{
	MENU_GAMES,
	MENU_SETTINGS,
	MENU_DEFAULT,
};

Menu currentMenu = MENU_GAMES;
Menu previousMenu = MENU_DEFAULT;

void switchMenuTo(Menu newMenu);
void goBack();

bool menuLoop()
{

	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.setDrawColor(1);
	u8g2.drawLine(0, 9, 128, 9);

	printCenter("Menu", 9);
	u8g2.setFontMode(1);
	u8g2.setFont(u8g2_font_6x13_mf);

	u8g2.setDrawColor(1);
	u8g2.drawBox(0, (9 * selectedOption) + 10, 128, 9);

	int optionsCount = 0;
	switch (currentMenu)
	{
	case MENU_GAMES:
		optionsCount = gameMenuLen;
		for (int i = 0; i < optionsCount; i++)
		{
			if (i != selectedOption)
				printCenter(gameMenuOptionsStrings[i].c_str(), ((i + 1) * 9) + 10);
		}
		u8g2.setDrawColor(0);
		printCenter(gameMenuOptionsStrings[selectedOption].c_str(), ((selectedOption + 1) * 9) + 10);
		break;

	case MENU_SETTINGS:
		optionsCount = settingsMenuLen;
		for (int i = 0; i < optionsCount; i++)
		{
			if (i != selectedOption)
			{
				printCenter(settingsMenuOptionsStrings[i].c_str(), ((i + 1) * 9) + 10);
			}
			if (settingsMenuOptionsTypes[i] == menutype_CHECKBOX)
			{
				u8g2.setDrawColor(i != selectedOption);
				u8g2.drawFrame(110, (i * 9) + 11, 7, 7);
				if ((i == 0 ? settings.soundEnabled : i == 1 ? settings.debugMode
																										 : false) == true)
					u8g2.drawBox(110, (i * 9) + 11, 7, 7);
				u8g2.setDrawColor(1);
			}
		}
		u8g2.setDrawColor(0);
		printCenter(settingsMenuOptionsStrings[selectedOption].c_str(), ((selectedOption + 1) * 9) + 10);
		break;
	};

	if (buttonIsPressed(NAME_UPBTN))
	{
		beep(600, 50);
		selectedOption--;
		if (selectedOption < 0)
			selectedOption = constrain(optionsCount - 1, 0, 5);
	}

	if (buttonIsPressed(NAME_DOWNBTN))
	{
		beep(400, 50);
		selectedOption++;
		if (selectedOption > constrain(optionsCount - 1, 0, 5))
			selectedOption = 0;
	}

	if (!digitalRead(CENTERBTN))
	{
		beep(200, 50);

		while (!digitalRead(CENTERBTN))
			yield();

		switch (currentMenu)
		{
		case MENU_GAMES:
			switch (selectedOption)
			{
			case 0:
				runningGame = GAME_PONG;
				break;
			case 1:
				runningGame = GAME_SNAKE;
				break;
			case 2:
				switchMenuTo(MENU_SETTINGS);
				break;
			}
			selectedOption = 0;

			break;
		case MENU_SETTINGS:
			switch (selectedOption)
			{
			case 0:
			if(settings.soundEnabled){
				settings.soundEnabled = false;
			}else{
				settings.soundEnabled = true;
        beep(1000, 50);
			}
			beep(800, 50);
				//saveSettings();
				break;
			case 1:
				settings.debugMode != settings.debugMode;
				//saveSettings();
			beep(800, 50);
				
				break;
			case 2:
				goBack();
				break;
			}
			break;
		};
	}

	return true;
}

void switchMenuTo(Menu newMenu)
{
	selectedOption = 0;
	previousMenu = currentMenu;
	currentMenu = newMenu;
};

void goBack()
{
	switchMenuTo(previousMenu);
}