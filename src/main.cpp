#include <Arduino.h>
#include "main.h"
#include "display.h"
#include "leds.h"
#include "network.h"
#include "buttons.h"
#include "gameEngine.h"
#include "bootimg.h"

int fps = 0;
int frameCounter = 0;
int targetFps = 20;
int temp = 0;

/* bool up = 0;
bool left = 0;
bool center = 0;
bool right = 0;
bool down = 0; */

void setup()
{
	Serial.begin(115200);
	loadSettings();
	
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
	u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_bootimg);
	delay(100);
	
	EEPROM.begin(512);
	loadSettings();
	
	pinMode(UPBTN, INPUT_PULLUP);
	pinMode(LEFTBTN, INPUT_PULLUP);
	pinMode(CENTERBTN, INPUT_PULLUP);
	pinMode(RIGHTBTN, INPUT_PULLUP);
	pinMode(DOWNBTN, INPUT_PULLUP);


	networkSetup();

	Serial.println("ledssetup begin");
	ledsSetup();
	setLedBrightness(10);
}

unsigned int lastFpsCalc = 0;
unsigned int buttonPressStart = 0;
bool buttonPressed = false;
unsigned int buttonPressEnd = 0;
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
		while (!digitalRead(RIGHTBTN) && !digitalRead(LEFTBTN) && settings.debugMode)
			processLoop();
		while (digitalRead(RIGHTBTN) && !digitalRead(LEFTBTN) && settings.debugMode)
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
	if (millis() - lastFpsCalc >= 1000)
	{
		lastFpsCalc = millis();
		fps = frameCounter;
		frameCounter = 0;
	}

	if (!digitalRead(UPBTN) || !digitalRead(LEFTBTN) || !digitalRead(RIGHTBTN) || !digitalRead(CENTERBTN) || !digitalRead(DOWNBTN))
	{
		lastUserInteraction = millis();
	}
	isAfk = (millis() - lastUserInteraction > 10000);
	if(isAfk != wasAfk){
		wasAfk = isAfk;
		if (isAfk && runningGame != GAME_PONG){
			temp = targetFps;
			targetFps = 5;
		}
		else{
			targetFps = temp;
		}
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

	if (newFrame)
	{
		displayLoop();
		ledsLoop();
		frameCounter++;
		newFrame = false;
	}

	yield();
}