#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "buttons.h"
#include "display.h"
#include "main.h"

enum RunningGame{
  MENU,
	PONG,
  SNAKE,
  FLAPPYBIRD,
  BREAKOUT,
};

extern RunningGame runningGame;

bool gameLoop();
#endif