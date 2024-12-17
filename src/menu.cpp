#include "gameEngine.h"

void menuSetup() {

};

bool menuLoop()
{

	if (!digitalRead(CENTERBTN))
		u8g2.drawStr(0, 24, String(millis() - buttonPressStart).c_str());
	else
		u8g2.drawStr(0, 16, String(buttonPressEnd - buttonPressStart).c_str());
	u8g2.setDrawColor(1);
	u8g2.drawBox(0, 0, 128, 48);
	u8g2.setDrawColor(0);
	u8g2.drawStr(0, 16, "MENU");
	if(!digitalRead(LEFTBTN)){
		
	}
	return true;
}