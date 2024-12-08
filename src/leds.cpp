#include "leds.h"

CRGB leds[NUM_LEDS];

bool ledsSetup()
{
	FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
	fillLeds(CRGB::Black);
	FastLED.show();
	return true;
}
void setLedBrightness(int value){
	FastLED.setBrightness(value);
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