#include "gameEngine.h"
#include "menu.h"
#include "settings.h"

void menuSetup() {
};

int selectedOption = 0;

bool (*optionsConditions[])(const Settings &) = {
		[](const Settings &settings)
		{ return settings.soundEnabled; }, // settingsmenuoption_SOUNDS
		[](const Settings &settings)
		{ return settings.menuSounds; }, // settingsmenuoption_MENUSOUNDS
		[](const Settings &settings)
		{ return settings.oneHanded; }, // settingsmenuoption_ONEHANDED
		nullptr,												// settingsmenuoption_BRIGHTNESS (if it's not a checkbox or doesn't need a condition)
		[](const Settings &settings)
		{ return settings.clientMode; }, // settingsmenuoption_CLIENTMODE
		[](const Settings &settings)
		{ return settings.debugMode; }, // settingsmenuoption_DEBUGMODE
		nullptr,												// settingsmenuoption_BACK (if it's not a checkbox or doesn't need a condition)
};

Menu currentMenu = MENU_GAMES;
Menu previousMenu = MENU_DEFAULT;

void switchMenuTo(Menu newMenu);
void goBack();

int scrollOffset = 0;
int optionsCount = 0;

void renderMenu()
{
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.setDrawColor(1);
	u8g2.drawLine(0, 9, 128, 9);

	switch (currentMenu)
	{
	case MENU_GAMES:

		printCenter("Fomenu", 9);
		u8g2.setFontMode(1);
		u8g2.setFont(u8g2_font_6x13_mf);

		u8g2.setDrawColor(1);
		if (selectedOption >= 0)
			u8g2.drawBox(0, (9 * selectedOption) + 10 + (scrollOffset * 9), 128, 9);

		optionsCount = gameMenuLen;
		for (int i = 0; i < optionsCount; i++)
		{
			int height = ((i + 1) * 9) + 10 + (scrollOffset * 9);
			
			u8g2.setDrawColor(i != selectedOption);
			
			if (height > 11)
				printCenter(gameMenuOptionsStrings[i].c_str(), height);
		}
		u8g2.setDrawColor(1);
		break;

	case MENU_SETTINGS:

		printCenter("Beallitasok", 9);
		u8g2.setFontMode(1);
		u8g2.setFont(u8g2_font_6x13_mf);

		u8g2.setDrawColor(1);
		if (selectedOption >= 0)
			u8g2.drawBox(0, (9 * selectedOption) + 10 + (scrollOffset * 9), 128, 9);

		if (selectedOption == settingsmenuoption_BRIGHTNESS)
		{
			fillLeds(0);
			leds[0].red = 255;
			leds[1].green = 255;
			leds[2].blue = 255;
			leds[3].red = 255;
			leds[3].green = 255;
		}
		else
		{
			fillLeds(0);
		}
		optionsCount = settingsMenuLen;
		for (int i = 0; i < optionsCount; i++)
		{
			int height = ((i + 1) * 9) + 10 + (scrollOffset * 9);
			if (height < 11)
				continue;

			bool baseColor = i != selectedOption;

			u8g2.setDrawColor(baseColor);
			printCenter(settingsMenuOptionsStrings[i].c_str(), height);
			if (settingsMenuOptionsTypes[i] == menutype_CHECKBOX)
			{
				u8g2.setDrawColor(baseColor);
				u8g2.drawFrame(110, height - 8, 7, 7);
				if (optionsConditions[i] != nullptr && optionsConditions[i](settings))
					u8g2.drawBox(110, height - 8, 7, 7);
			}
			else if (settingsMenuOptionsTypes[i] == menutype_NUMBER)
			{
				u8g2.setDrawColor(baseColor);
				String temp = "";
				switch (i)
				{
				case settingsmenuoption_BRIGHTNESS:
					if (settings.brightness > 0 && settings.brightness != 255)
					{
						temp += map(settings.brightness, 0, 255, 0, 100);
						temp += "%";
					}
					else
					{
						if (settings.brightness == 0)
							temp += "Ki";
						else
							temp += "MAX";
					}
					break;
				}
				u8g2.drawStr(110, height, temp.c_str());
			}
		}
		u8g2.setDrawColor(1); // Reset draw color
		break;
	};
};

bool menuLoop()
{

	if (settings.debugMode)
	{
		nextLine();
		u8g2.setFont(u8g2_font_4x6_mf);
		u8g2.print(selectedOption);
		nextLine();
		u8g2.print(scrollOffset);
		nextLine();
	}

	if (buttonIsPressed(NAME_UPBTN))
	{
		beep(600, 50, BEEPTYPE_MENU);
		selectedOption--;
		if (currentMenu == MENU_GAMES && selectedOption == gamemenuoption_SPLIT1)
			selectedOption--;
	}

	if (buttonIsPressed(NAME_DOWNBTN))
	{
		beep(400, 50, BEEPTYPE_MENU);
		selectedOption++;
		if (currentMenu == MENU_GAMES && selectedOption == gamemenuoption_SPLIT1)
			selectedOption++;
	}

	selectedOption = constrain(selectedOption, 0, optionsCount - 1);

	if (scrollOffset * -1 - 1 == selectedOption && optionsCount > 6)
	{
		scrollOffset++;
	}

	if (scrollOffset * -1 + 6 == selectedOption && selectedOption > 5 && optionsCount > 6)
	{
		scrollOffset--;
	}

	// if (currentMenu != MENU_SETTINGS)
	//	scrollOffset = 0;

	if (LEFTPressed() || RIGHTPressed())
	{
		switch (currentMenu)
		{
		case MENU_SETTINGS:
			switch (selectedOption)
			{
			case settingsmenuoption_BRIGHTNESS:
				if (buttonIsPressed(NAME_LEFTBTN))
					settings.brightness = settings.brightness - (CENTERPressed() ? 20 : 5);
				if (buttonIsPressed(NAME_RIGHTBTN))
					settings.brightness = settings.brightness + (CENTERPressed() ? 20 : 5);
				settings.brightness = constrain(settings.brightness, 0, 255);
				FastLED.setBrightness(settings.brightness);
				break;
			}
			break;
		}
	}

	if (CENTERPressed())
	{

		while (CENTERPressed())
			processLoop();

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
			case gamemenuoption_TEST:
				runningGame = GAME_TEST;
				break;
			case gamemenuoption_BREAKOUT:
				runningGame = GAME_BREAKOUT;
				break;
			case gamemenuoption_SETTINGS:
				switchMenuTo(MENU_SETTINGS);
				break;
			case gamemenuoption_RESTART:
				u8g2.clearDisplay();
				u8g2.sendBuffer();
				fillLeds(CRGB::Black);
				ledsLoop();
				ESP.restart();
				break;
			}
			selectedOption = 0;

			break;
		case MENU_SETTINGS:
			switch (selectedOption)
			{
			case settingsmenuoption_SOUNDS:
				settings.soundEnabled = !settings.soundEnabled;
				if (!settings.soundEnabled)
					noTone(25);
				break;
			case settingsmenuoption_MENUSOUNDS:
				settings.menuSounds = !settings.menuSounds;
				break;
			case settingsmenuoption_DEBUGMODE:
				settings.debugMode = !settings.debugMode;
				break;

			case settingsmenuoption_BACK:
				saveSettings();
				goBack();
				break;
			case settingsmenuoption_ONEHANDED:
				settings.oneHanded = !settings.oneHanded;
				break;
			}
			if (settingsMenuOptionsTypes[selectedOption] == menutype_CHECKBOX)
			{
				beep(800, 50, BEEPTYPE_MENU);
			}
			if (optionsConditions[selectedOption] != nullptr && optionsConditions[selectedOption](settings))
				beep(1000, 50, BEEPTYPE_MENU);
			break;
		};
		beep(200, 50, BEEPTYPE_MENU);
	}

	renderMenu();

	return true;
}

void switchMenuTo(Menu newMenu)
{
	selectedOption = 0;
	scrollOffset = 0;
	previousMenu = currentMenu;
	currentMenu = newMenu;
};

void goBack()
{
	switchMenuTo(previousMenu);
}