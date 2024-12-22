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

bool gameLoop();
#endif