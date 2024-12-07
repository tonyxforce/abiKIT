#include "display.h"

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, -1, 21, 22);

bool displaySetup()
{
  Wire.begin(21, 22);
	if (!u8g2.begin())
		return false; // an error occurred, return false
	
	return true; // no error, return true
}

bool displayLoop(){
	u8g2.sendBuffer(); //update display
	return true; // reserved for error handling
}