#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "buttons.h"
#include "display.h"
#include "main.h"
#include "leds.h"
#include "buzzer.h"
#include "settings.h"

enum RunningGame{
  GAME_MENU,
	GAME_PONG,
  GAME_SNAKE,
  GAME_FLAPPYBIRD,
  GAME_BREAKOUT,
	GAME_DEFAULT,
};

extern RunningGame runningGame;

bool gameLoop();
#endif