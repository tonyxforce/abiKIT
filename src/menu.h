#ifndef MENU_H
#define MENU_H

bool menuLoop();
void menuSetup();

enum MenuType
{
	menutype_GENERAL,
	menutype_CHECKBOX,
	menutype_NUMBER,
};

const int gameMenuLen = 7;
enum GameMenuOption
{
	gamemenuoption_TEST,
	gamemenuoption_PONG,
	gamemenuoption_SNAKE,
	gamemenuoption_BREAKOUT,
	gamemenuoption_SPLIT1,
	gamemenuoption_SETTINGS,
	gamemenuoption_RESTART,
};

const String gameMenuOptionsStrings[gameMenuLen] = {
		"Hardware teszt",
		"Pong",
		"Snake",
		"Breakout",
		"",
		"Beallitasok",
		"Ujrainditas"};

const int settingsMenuLen = 7;
enum SettingsMenuOption
{
	settingsmenuoption_SOUNDS,
	settingsmenuoption_MENUSOUNDS,
	settingsmenuoption_ONEHANDED,
	settingsmenuoption_BRIGHTNESS,
	settingsmenuoption_CLIENTMODE,
	settingsmenuoption_DEBUGMODE,
	settingsmenuoption_BACK,
};

const String settingsMenuOptionsStrings[settingsMenuLen] = {
		"Hang",
		"Menu hang",
		"Egykezes mod",
		"Fenyero",
		"Kliens mod",
		"Debug mod",
		"Vissza",
};

const MenuType settingsMenuOptionsTypes[settingsMenuLen] = {
		menutype_CHECKBOX,
		menutype_CHECKBOX,
		menutype_CHECKBOX,
		menutype_NUMBER,
		menutype_CHECKBOX,
		menutype_CHECKBOX,
		menutype_GENERAL,
};

enum Menu
{
	MENU_GAMES,
	MENU_SETTINGS,
	MENU_DEFAULT,
};

extern Menu currentMenu;
extern int selectedOption;
void goBack();
void switchMenuTo(Menu newMenu);

#endif