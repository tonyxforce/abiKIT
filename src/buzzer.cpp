#include "buzzer.h"

void beep(unsigned int frequency, unsigned long duration /* = 0UL */)
{
	if(soundOn)
	tone(25, frequency, duration);
};