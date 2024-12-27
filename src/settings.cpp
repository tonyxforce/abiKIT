#include "settings.h"

/*
	char version[4];
	int brightness;
	bool debugMode;
	bool menuSounds;
	bool oneHanded;
	bool soundEnabled;
	bool clientMode;
	uint8_t resetCounter, wdtCounter;
	 */
Settings settings = {
		CONFIG_VERSION, // version
		100,						// brightness
		false,					// debugMode
		true,						// menusounds
		false,					// oneHanded
		true,						// soundEnabled
		false,					// clientMode
		false,					// showFps
};

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
	}
	else
	{
		saveSettings();
	}
}