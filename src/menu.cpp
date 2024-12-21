#include "gameEngine.h"
#include "menu.h"
#include "settings.h"

void menuSetup() {

};

int selectedOption = 0;

enum MenuType
{
	menutype_GENERAL,
	menutype_CHECKBOX,
	menutype_NUMBER,
};

const int gameMenuLen = 5;

enum GameMenuOption
{
	gamemenuoption_PONG,
	gamemenuoption_SNAKE,
	gamemenuoption_SETTINGS,
	gamemenuoption_SHUTDOWN,
	gamemenuoption_RESTART,
};

String gameMenuOptionsStrings[gameMenuLen] = {
		"Pong",
		"Snake",
		"Beallitasok",
		"Leallitas",
		"Ujrainditas"};

const int settingsMenuLen = 5;
enum SettingsMenuOption
{
	settingsmenuoption_SOUNDS,
	settingsmenuoption_MENUSOUNDS,
	settingsmenuoption_DEBUGMODE,
	settingsmenuoption_BRIGHTNESS,
	settingsmenuoption_BACK,
};

String settingsMenuOptionsStrings[settingsMenuLen] = {
		"Hang ki/be",
		"Menu hang ki/be",
		"Debug mod ki/be",
		"Fenyero",
		"Vissza",
};

MenuType settingsMenuOptionsTypes[settingsMenuLen] = {
		menutype_CHECKBOX,
		menutype_CHECKBOX,
		menutype_CHECKBOX,
		menutype_NUMBER,
		menutype_GENERAL,
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
		if(selectedOption == settingsmenuoption_BRIGHTNESS){
								fillLeds(0);
					leds[0].red = 255;
					leds[1].green = 255;
					leds[2].blue = 255;
					leds[3].red = 255;
					leds[3].green = 255;
		}else{
			fillLeds(0);
		}
		optionsCount = settingsMenuLen;
		for (int i = 0; i < optionsCount; i++)
		{
			bool baseColor = i != selectedOption;
			bool invertedColor = !baseColor;
			int height = ((i + 1) * 9) + 10;
			u8g2.setDrawColor(baseColor);
			printCenter(settingsMenuOptionsStrings[i].c_str(), height);
			if (settingsMenuOptionsTypes[i] == menutype_CHECKBOX)
			{
				u8g2.setDrawColor(baseColor);
				u8g2.drawFrame(110, height - 8, 7, 7);
				if ((i == settingsmenuoption_SOUNDS ? settings.soundEnabled : i == settingsmenuoption_DEBUGMODE ? settings.debugMode
																																	: i == settingsmenuoption_MENUSOUNDS	? settings.menuSounds
																																																				: false) == true)
					u8g2.drawBox(110, height - 8, 7, 7);
			}
			else if (settingsMenuOptionsTypes[i] == menutype_NUMBER)
			{
				u8g2.setDrawColor(baseColor);
				String temp = "";
				switch (i)
				{
				case settingsmenuoption_BRIGHTNESS:
					temp += map(settings.brightness, 0, 255, 0, 100);
					break;
				}
				temp += "%";
				u8g2.drawStr(90, height, temp.c_str());
			}
		}
		u8g2.setDrawColor(1); // Reset draw color
		break;
	};

	if (buttonIsPressed(NAME_UPBTN))
	{
		beep(600, 50, BEEPTYPE_MENU);
		selectedOption--;
		if (selectedOption < 0)
			selectedOption = constrain(optionsCount - 1, 0, 5);
	}

	if (buttonIsPressed(NAME_DOWNBTN))
	{
		beep(400, 50, BEEPTYPE_MENU);
		selectedOption++;
		if (selectedOption > constrain(optionsCount - 1, 0, 5))
			selectedOption = 0;
	}
	
	if (!digitalRead(LEFTBTN) || !digitalRead(RIGHTBTN))
	{
		switch (currentMenu)
		{
		case MENU_SETTINGS:
			switch (selectedOption)
			{
			case settingsmenuoption_BRIGHTNESS:
				if (buttonIsPressed(NAME_LEFTBTN))
					settings.brightness = settings.brightness - (!digitalRead(CENTERBTN) ? 20 : 5);
				if (buttonIsPressed(NAME_RIGHTBTN))
					settings.brightness = settings.brightness + (!digitalRead(CENTERBTN) ? 20 : 5);
				settings.brightness = constrain(settings.brightness, 0, 255);
				FastLED.setBrightness(settings.brightness);
				break;
			}
			break;
		}
	}

	if (!digitalRead(CENTERBTN))
	{

		while (!digitalRead(CENTERBTN))
			yield();

		switch (currentMenu)
		{
		case MENU_GAMES:
			switch (selectedOption)
			{
			case gamemenuoption_PONG:
				runningGame = GAME_PONG;
				break;
			case gamemenuoption_SNAKE:
				runningGame = GAME_SNAKE;
				break;
			case gamemenuoption_SETTINGS:
				switchMenuTo(MENU_SETTINGS);
				break;
			case gamemenuoption_SHUTDOWN:
				u8g2.clearDisplay();
				u8g2.sendBuffer();
				fillLeds(CRGB::Black);
				ledsLoop();
				esp_deep_sleep_start();
				break;
			case gamemenuoption_RESTART:
				ESP.restart();
				break;
			}
			selectedOption = 0;

			break;
		case MENU_SETTINGS:
			switch (selectedOption)
			{
			case settingsmenuoption_SOUNDS:
				if (settings.soundEnabled)
				{
					settings.soundEnabled = false;
				}
				else
				{
					settings.soundEnabled = true;
				}
				break;
			case settingsmenuoption_MENUSOUNDS:
				if (settings.menuSounds)
				{
					settings.menuSounds = false;
				}
				else
				{
					settings.menuSounds = true;
				}

				break;
			case settingsmenuoption_DEBUGMODE:
				if (settings.debugMode)
				{
					settings.debugMode = false;
				}
				else
				{
					settings.debugMode = true;
				}
				break;

			case settingsmenuoption_BACK:
				saveSettings();
				goBack();
				break;
			}
			if (settingsMenuOptionsTypes[selectedOption] == menutype_CHECKBOX)
			{
				beep(1000, 50, BEEPTYPE_MENU);
				beep(800, 50, BEEPTYPE_MENU);
			}
			break;
		};
		beep(200, 50, BEEPTYPE_MENU);
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