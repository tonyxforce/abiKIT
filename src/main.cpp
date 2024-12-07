#include <Arduino.h>
#include "main.h"
#include "display.h"
#include "buttons.h"
#include "leds.h"

bool *up = 0;
bool *left = 0;
bool *center = 0;
bool *right = 0;
bool *down = 0;

void setup()
{
	Serial.begin(115200);
	Serial.println("displaysetup begin");
	delay(10);
	if (!displaySetup())
	{
		Serial.println("Display setup failed");
	}
	else
	{
		Serial.println("Display setup succeeded");
	}
	Serial.println("buttonsetup begin");
	buttonsSetup();
	Serial.println("ledssetup begin");
	ledsSetup();
}

void loop()
{
	buttonsLoop(*up, *left, *center, *right, *down);

	u8g2.setCursor(0, 8);
	u8g2.setFont(u8g2_font_t0_11_tf);
	u8g2.print("Hello World!");

	fillLeds(up ? CRGB::Red : (left ? CRGB::Green : (center ? CRGB::Blue : (right ? CRGB::Cyan : (down ? CRGB::White : CRGB::Black)))));
	ledsLoop();
	displayLoop();
}