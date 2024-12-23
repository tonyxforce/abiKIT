#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "buttons.h"
#include "display.h"
#include "main.h"
#include "leds.h"
#include "buzzer.h"
#include "settings.h"

enum Game{
  GAME_MENU,
	GAME_PONG,
  GAME_SNAKE,
  GAME_FLAPPYBIRD,
  GAME_BREAKOUT,
	GAME_DEFAULT,
	GAME_TEST,
};

extern Game runningGame;

extern int paddle1Y, paddle2Y, ballX, ballY, ballVelX, ballVelY, score1, score2; // Pong variables
extern int paddleX; // Breakout variables

extern bool player1Auto, player2Auto;
extern unsigned long lastUserInput, lastPacketTime;

bool gameLoop();
#endif