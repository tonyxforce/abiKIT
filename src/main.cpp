#include <Arduino.h>
#include "main.h"
#include "display.h"
#include "leds.h"

#define UPBTN 18
#define LEFTBTN 16
#define CENTERBTN 17
#define RIGHTBTN 23
#define DOWNBTN 19

float fps = 0;
int frameCounter = 0;



bool up = 0;
bool left = 0;
bool center = 0;
bool right = 0;
bool down = 0;

void setup()
{
	pinMode(UPBTN, INPUT_PULLUP);
	pinMode(LEFTBTN, INPUT_PULLUP);
	pinMode(CENTERBTN, INPUT_PULLUP);
	pinMode(RIGHTBTN, INPUT_PULLUP);
	pinMode(DOWNBTN, INPUT_PULLUP);

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
	Serial.println("ledssetup begin");
	ledsSetup();
}

unsigned int lastFpsCalc = 0;

void loop()
{
	frameCounter++;
	if (millis() - lastFpsCalc >= 1000)
	{
		lastFpsCalc = millis();
		fps = frameCounter;
		frameCounter = 0;
	}
	up = !digitalRead(UPBTN);
	left = !digitalRead(LEFTBTN);
	center = !digitalRead(CENTERBTN);
	right = !digitalRead(RIGHTBTN);
	down = !digitalRead(DOWNBTN);

	u8g2.setFont(u8g2_font_t0_11_tf);
	u8g2.print("FPS: ");
	u8g2.print(fps);
	nextLine();

	ledsLoop();
	displayLoop();
}