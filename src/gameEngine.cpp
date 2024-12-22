#include "gameEngine.h"
#include "games/pong.h"
#include "games/snake/snake-game.h"
#include "games/test/test.h"
#include "menu.h"

Game runningGame = GAME_MENU;
Game runningGameBef = GAME_DEFAULT;

bool gameLoop()
{
	if (runningGame != runningGameBef)
	{
		fillLeds(0);

		beep(1000, 50, BEEPTYPE_MENU);

		switch (runningGame)
		{
		case GAME_MENU:
			menuSetup();
			targetFps = 1000;
			break;
		case GAME_PONG:
			pongSetup();
			targetFps = 20;

			break;
		case GAME_SNAKE:
			snakeSetup();
			targetFps = 20;
			break;
		case GAME_TEST:
			testSetup();
			targetFps = 1000;
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
	case GAME_TEST:
		testLoop();
		return true;
		break;
	}
	return false;
}