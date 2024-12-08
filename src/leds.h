#ifndef LEDS_H
#define LEDS_H

#include <FastLED.h>
#define NUM_LEDS 4
#define DATA_PIN 26

extern CRGB leds[];

bool ledsSetup();
void ledsLoop();

void fillLeds(CRGB color);
void setLedBrightness(int value);

#endif