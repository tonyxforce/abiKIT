#ifndef SETTINGS_H
#define SETTINGS_H

#define CONFIG_VERSION "010"

// Dont change this
#define CONFIG_START 0

#include "main.h"
#include "EEPROM.h"

struct Settings
{
	char version[4];
	int brightness;
	bool debugMode;
	bool menuSounds;
	bool soundEnabled;
	uint8_t resetCounter, wdtCounter;
};

extern Settings settings;
void saveSettings();
void loadSettings();
#endif