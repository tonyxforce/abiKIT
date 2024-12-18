#include "buzzer.h"
#include "settings.h"

void beep(unsigned int frequency, unsigned long duration /* = 0UL */)
{
	if(settings.soundEnabled)
	tone(25, frequency, duration);
};