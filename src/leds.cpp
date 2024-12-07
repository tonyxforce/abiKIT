#include "leds.h"

CRGB leds[NUM_LEDS];

bool ledsSetup()
{
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	return true;
}

void ledsLoop()
{
	FastLED.show();
}

void fillLeds(CRGB colors){
	for(int i = 0; i<NUM_LEDS; i++){
		leds[i] = colors;
	}
};