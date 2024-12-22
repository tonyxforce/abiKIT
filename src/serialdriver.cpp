#include "serialdriver.h"

void serialDriverSetup()
{
	Serial.begin(921600);
};

void serialDriverLoop()
{
	if (Serial.available() > 1)
	{
		char firstChar = Serial.read();
		char secondChar = Serial.read();

		switch (firstChar - '0')
		{
		case FIRSTCHAR_GAME: // Switch games
			switch (secondChar)
			{
			case '0':
				runningGame = GAME_MENU;
				break;
			case '1':
				runningGame = GAME_TEST;
				break;
			case '2':
				runningGame = GAME_PONG;
				break;
			case '3':
				runningGame = GAME_SNAKE;
				break;
			}
			break;
		case FIRSTCHAR_MENU: // Switch menu
			switch (secondChar)
			{
			case '0':
				switchMenuTo(MENU_GAMES);
				break;
			case '1':
				switchMenuTo(MENU_SETTINGS);
				break;
			case '2':
				goBack();
			}
			break;
		case FIRSTCHAR_SELECTED: // Switch selectedOption
			if (Serial.available() > 0)
				selectedOption = ((secondChar - '0') * 10 + (Serial.read() - '0'));
			break;
		}
	}

	while (Serial.available())
		Serial.read();
};