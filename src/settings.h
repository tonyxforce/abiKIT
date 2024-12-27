#ifndef SETTINGS_H
#define SETTINGS_H

#define CONFIG_VERSION "003"

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
	bool oneHanded;
	bool soundEnabled;
	bool clientMode;
	bool showFps;
};

extern Settings settings;
void saveSettings();
void loadSettings();
#endif