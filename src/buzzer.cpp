#include "buzzer.h"
#include "settings.h"

void beep(unsigned int frequency, unsigned long duration, Beeptype beeptype)
{
	if(settings.soundEnabled && beeptype == BEEPTYPE_GAME)
	tone(25, frequency, duration);
	else if(settings.menuSounds && settings.soundEnabled && beeptype == BEEPTYPE_MENU)
	tone(25, frequency, duration);
};