#ifndef SERIALDRIVER_H
#define SERIALDRIVER_H

#include <Arduino.h>
#include "settings.h"
#include "gameEngine.h"
#include "menu.h"

void serialDriverSetup();
void serialDriverLoop();

enum SerialFirstChar{
	FIRSTCHAR_GAME,
	FIRSTCHAR_MENU,
	FIRSTCHAR_SELECTED
};

#endif