#include "gameEngine.h"
#include "games/pong.h"
#include "games/snake/snake-game.h"
#include "games/test/test.h"
#include "menu.h"
#include "games/breakout/breakout.h"

int paddleX;

int paddle1Y, paddle2Y;
int ballX, ballY;
int ballVelX, ballVelY;

int score1;
int score2;

bool player1Auto;
bool player2Auto;

unsigned long lastUserInput;
unsigned long lastPacketTime;

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
		case GAME_BREAKOUT:
			breakoutSetup();
			targetFps = 20;
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
	case GAME_BREAKOUT:
		return breakoutLoop();
		break;
	}
	return false;
}