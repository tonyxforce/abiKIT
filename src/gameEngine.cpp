#include "gameEngine.h"
#include "games/pong.h"
#include "games/snake/snake-game.h"
#include "menu.h"

RunningGame runningGame = GAME_MENU;
RunningGame runningGameBef = GAME_MENU;

bool debugMode = false; // // TODO: change this in production
bool soundOn = false; // TODO: change this in production

bool gameLoop()
{
	if (runningGame != runningGameBef)
	{
		fillLeds(0);

		tone(25, 1000, 50);

		switch (runningGame)
		{
		case GAME_MENU:
			menuSetup();
			break;
		case GAME_PONG:
			pongSetup();
			break;
		case GAME_SNAKE:
			snakeSetup();
			break;
		}
		runningGameBef = runningGame;
	}
	switch (runningGame)
	{
	case GAME_MENU:
		return menuLoop();
		break;
	case GAME_PONG:
		pongLoop();
		return true;
		break;
	case GAME_SNAKE:
		snakeLoop();
		return true;
		break;
	}
	return false;
}