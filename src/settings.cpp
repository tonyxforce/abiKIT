#include "settings.h"

Settings settings = {
		CONFIG_VERSION,
		10,
		false,
		true,
		0, 0};

/*
	char version[4];
	int brightness;
	bool debugMode;
	bool soundEnabled;
	uint8_t resetCounter, wdtCounter;
	 */

void saveSettings()
{
	for (uint16_t t = 0; t < sizeof(settings); t++)
		EEPROM.write(CONFIG_START + t, *((char *)&settings + t));

	EEPROM.commit();
}

void loadSettings()
{
	// To make sure there are settings, and they are YOURS!
	// If nothing is found it will use the default settings.
	if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
			EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
			EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2])
	{

		// Store defaults for if we need them
		Settings tmpStore;
		tmpStore = settings;

		// Copy data to deviceSettings structure
		for (uint16_t t = 0; t < sizeof(settings); t++)
			*((char *)&settings + t) = EEPROM.read(CONFIG_START + t);

		// If we want to restore all our settings
		if (settings.resetCounter >= 5 || settings.wdtCounter >= 10)
		{
			settings.wdtCounter = 0;
			settings.resetCounter = 0;

			// Store defaults back into main settings
			settings = tmpStore;
		}

		// If config files dont match, save defaults then erase the ESP config to clear away any residue
	}
	else
	{
		saveSettings();
	}
}