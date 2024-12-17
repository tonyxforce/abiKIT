#include <Arduino.h>
#include "main.h"
#include "display.h"
#include "leds.h"
#include "network.h"
#include "buttons.h"
#include "gameEngine.h"

float fps = 0;
int frameCounter = 0;
int targetFps = 20;

/* bool up = 0;
bool left = 0;
bool center = 0;
bool right = 0;
bool down = 0; */

void setup()
{
	pinMode(UPBTN, INPUT_PULLUP);
	pinMode(LEFTBTN, INPUT_PULLUP);
	pinMode(CENTERBTN, INPUT_PULLUP);
	pinMode(RIGHTBTN, INPUT_PULLUP);
	pinMode(DOWNBTN, INPUT_PULLUP);

	Serial.begin(115200);

	networkSetup();

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
	setLedBrightness(10);
}

unsigned int lastFpsCalc = 0;
unsigned int buttonPressStart = 0;
bool buttonPressed = false;
unsigned int buttonPressEnd = 0;
unsigned int lastFrameTime = 0;

void enterMenu();
void processLoop();

bool newFrame = false;

void loop()
{
	processLoop();

	u8g2.setCursor(0, 6);
	u8g2.setFont(u8g2_font_4x6_mf);
	u8g2.print(fps);

	if (millis() - lastFrameTime >= (1000 / targetFps))
	{
		newFrame = gameLoop();
		while (!digitalRead(RIGHTBTN) && !digitalRead(LEFTBTN))
			processLoop();
		while (digitalRead(RIGHTBTN) && !digitalRead(LEFTBTN))
			processLoop();
	}
	if (newFrame)
	{
		displayLoop();
		ledsLoop();
		frameCounter++;
		lastFrameTime = millis();
		newFrame = false;
	}
}

void enterMenu()
{
	runningGame = GAME_MENU;
}

void processLoop()
{
	if (millis() - lastFpsCalc >= 1000)
	{
		lastFpsCalc = millis();
		fps = frameCounter;
		frameCounter = 0;
	}
	if (!digitalRead(CENTERBTN) && !buttonPressed)
	{
		buttonPressStart = millis();
		buttonPressed = true;
	};
	if (digitalRead(CENTERBTN) && buttonPressed)
	{
		buttonPressEnd = millis();
		buttonPressed = 0;
	};

	if (millis() - buttonPressStart >= 1000 && buttonPressed)
	{
		while (!digitalRead(CENTERBTN))
			yield();
		enterMenu();
	};

	yield();
}