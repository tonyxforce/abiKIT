#include <Arduino.h>
#include "main.h"
#include "display.h"
#include "leds.h"
#include "network.h"
#include "buttons.h"
#include "gameEngine.h"
#include "bootimg.h"
#include "serialdriver.h"
#include "OTA.h"

int fps = 0;
int frameCounter = 0;
int targetFps = 20;
int tempFps = 0;

/* bool up = 0;
bool left = 0;
bool center = 0;
bool right = 0;
bool down = 0; */

void setup()
{
	serialDriverSetup();
	EEPROM.begin(512);
	loadSettings();

	ledsSetup();
	setLedBrightness(settings.brightness);

	delay(10);
	displaySetup();
	// u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_bootimg);
	// u8g2.sendBuffer();
	// delay(500);
	u8g2.clearBuffer();
	u8g2.sendBuffer();

	pinMode(UPBTN, INPUT_PULLUP);
	pinMode(LEFTBTN, INPUT_PULLUP);
	pinMode(CENTERBTN, INPUT_PULLUP);
	pinMode(RIGHTBTN, INPUT_PULLUP);
	pinMode(DOWNBTN, INPUT_PULLUP);

	networkSetup();
	otaSetup();
}

unsigned int lastFpsCalc = 0;
unsigned int buttonPressStart = 0;
bool buttonPressed = false;
unsigned int lastFrameRequestTime = 0;
unsigned int lastUserInteraction = 0;
bool isAfk = 0;
bool wasAfk = 0;

void enterMenu();
void processLoop();

bool newFrame = false;

void loop()
{
	processLoop();
	buttonsLoop();

	u8g2.setDrawColor(1);
	u8g2.setCursor(0, 6);
	u8g2.setFont(u8g2_font_4x6_mf);
	u8g2.print(fps);
	u8g2.print("FPS");
	nextLine();

	if (millis() - lastFrameRequestTime >= (1000 / targetFps))
	{
		newFrame = gameLoop();
		while (!RIGHTPressed() && LEFTPressed() && settings.debugMode)
			processLoop();
		while (RIGHTPressed() && LEFTPressed() && settings.debugMode)
			processLoop();
		lastFrameRequestTime = millis();
	}
}

void enterMenu()
{
	runningGame = GAME_MENU;
}

void processLoop()
{
	checkButtons();
	serialDriverLoop();
	otaLoop();

	if (millis() - lastFpsCalc >= 1000)
	{
		lastFpsCalc = millis();
		fps = frameCounter;
		frameCounter = 0;
	}

	if ((!settings.oneHanded ? CENTERPressed() : LEFTPressed()) && !buttonPressed)
	{
		buttonPressStart = millis();
		buttonPressed = true;
	};
	if (!(!settings.oneHanded ? CENTERPressed() : LEFTPressed()) && buttonPressed)
	{
		buttonPressed = 0;
	};

	if (millis() - buttonPressStart >= 1000 && buttonPressed && (runningGame == GAME_TEST ? ALLPressed() : true))
	{
		while ((settings.oneHanded ? LEFTPressed() : (runningGame == GAME_TEST ? ALLPressed() : CENTERPressed())))
			yield();
		enterMenu();
	};

	if (newFrame)
	{
		displayLoop();
		ledsLoop();
		frameCounter++;
		newFrame = false;
	}

	yield();
}