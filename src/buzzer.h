#ifndef BUZZER_H
#define BUZZER_H
#include <Arduino.h>
#include "gameEngine.h"

enum Beeptype{
	BEEPTYPE_GAME,
	BEEPTYPE_MENU
};

void beep(unsigned int frequency, unsigned long duration = 0UL, Beeptype beeptype);

#endif