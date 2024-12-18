#include "gameEngine.h"

void menuSetup() {

};

int selectedOption = 0;

enum GameMenuOption
{
	gamemenuoption_PONG,
	gamemenuoption_SNAKE,
	gamemenuoption_SETTINGS,
	gamemenuoption_EXIT,
};

String gameMenuOptionsStrings[] = {
		"Pong",
		"Snake",
		"Beallitasok",
		"Kilepes"};

enum SettingsMenuOption
{
	settingsmenuoption_SOUNDS,
	settingsmenuoption_DEBUGMODE,
	settingsmenuoption_BACK
};

String settingssMenuOptionsStrings[] = {
		"Hang ki/be",
		"Debug mod ki/be",
		"Vissza"};

enum MenuType
{
	menutype_BOOLEAN,
	menutype_NUMBER,
	menutype_MENU,
	menutype_BUTTON,
};

MenuType settingsMenuOptionsTypes[] = {
		menutype_BOOLEAN,
		menutype_BOOLEAN,
		menutype_BUTTON
};

enum Menu
{
	MENU_GAMES,
	MENU_SETTINGS
};

Menu currentMenu = MENU_GAMES;

bool menuLoop()
{

	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.setDrawColor(1);
	u8g2.drawLine(0, 9, 128, 9);

	printCenter("Menu", 9);

	u8g2.setDrawColor(1);
	u8g2.drawBox(0, (9 * selectedOption) + 10, 128, 9);

	int optionsCount = 0;
	switch (currentMenu)
	{
	case MENU_GAMES:
		optionsCount = gameMenuOptionsStrings->length();
		for (int i = 0; i < optionsCount; i++)
		{
			if (i != selectedOption)
				printCenter(gameMenuOptionsStrings[i].c_str(), ((i + 1) * 9) + 10);
		}
		u8g2.setDrawColor(0);
		printCenter(gameMenuOptionsStrings[selectedOption].c_str(), ((selectedOption + 1) * 9) + 10);
		break;
		case MENU_SETTINGS:
		optionsCount = settingssMenuOptionsStrings->length();
		for (int i = 0; i < optionsCount; i++)
		{
			if (i != selectedOption)
				printCenter(settingssMenuOptionsStrings[i].c_str(), ((i + 1) * 9) + 10);
		}
		u8g2.setDrawColor(0);
		printCenter(settingssMenuOptionsStrings[selectedOption].c_str(), ((selectedOption + 1) * 9) + 10);
		break;
	};

	if (buttonIsPressed(NAME_UPBTN))
	{
		beep(600, 50);
		selectedOption--;
		if (selectedOption < 0)
			selectedOption = min(5, optionsCount - 1);
	}

	if (buttonIsPressed(NAME_DOWNBTN))
	{
		beep(400, 50);
		selectedOption++;
		if (selectedOption > min(5, optionsCount - 1))
			selectedOption = 0;
	}

	if (!digitalRead(CENTERBTN))
	{
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
				currentMenu = MENU_SETTINGS;
				break;
			case 3:
			break;
			}
			break;
		case MENU_SETTINGS:
			switch (selectedOption)
			{
			}
			break;
		};
		selectedOption = 0;
	}

	return true;
}