#include "display.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 1, 22, 21);

int lineCount = 0;

bool displaySetup()
{
	Wire.begin(21, 22);
	if (!u8g2.begin())
		return false; // an error occurred, return false

	return true; // no error, return true
}

bool displayLoop()
{
	u8g2.sendBuffer(); // update display
	u8g2.setCursor(0, 8); // set cursor to next line
	lineCount = 0;
	return true;			 // reserved for error handling
}

void nextLine()
{
	if (lineCount == 6)
	{
		u8g2.clearBuffer(); // clear screen
		lineCount = 0;
	}
	else
	{
		lineCount++;
	}
	u8g2.setCursor(0, lineCount == 0 ? 8 : lineCount * 9);
}

void printText(String text)
{
	u8g2.print(text);
	nextLine();
}
void printText(double text)
{
	u8g2.print(text);
	nextLine();
}