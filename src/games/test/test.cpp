#include "test.h"

void testSetup() {

};

int y = 0;
uint8_t a = 0;
void switchToNextLine();
void printRight(String text);

CRGB::HTMLColorCode color = CRGB::Black;

void testLoop()
{

	color = UPPressed()				? CRGB::Black
					: LEFTPressed()		? CRGB::Red
					: CENTERPressed() ? CRGB::Green
					: RIGHTPressed()	? CRGB::Blue
					: DOWNPressed()		? CRGB::White
														: color;

	fillLeds(color);

	switch (color)
	{
	case CRGB::Red:
		beep(200, (1000 / fps), BEEPTYPE_GAME);
		break;
	case CRGB::Green:
		beep(400, (1000 / fps), BEEPTYPE_GAME);
		break;
	case CRGB::Blue:
		beep(600, (1000 / fps), BEEPTYPE_GAME);
		break;
	case CRGB::White:
		beep(800, (1000 / fps), BEEPTYPE_GAME);
		break;
	case CRGB::Yellow:
		beep(1000, (1000 / fps), BEEPTYPE_GAME);
		break;
	}

	y = 9;
	u8g2.setFont(u8g2_font_6x13_mf);

	printRight(!UPPressed() ? "Fel ki" : "Fel be");
	switchToNextLine();
	printRight(!LEFTPressed() ? "Bal ki" : "Bal be");
	switchToNextLine();
	printRight(!CENTERPressed() ? "Kozep ki" : "Kozep be");
	switchToNextLine();
	printRight(!RIGHTPressed() ? "Jobb ki" : "Jobb be");
	switchToNextLine();
	printRight(!DOWNPressed() ? "Le ki" : "Le be");
	switchToNextLine();

	a++;
	u8g2.print(a);

	checkButtons();

	switchToNextLine();
	u8g2.print(buttonIsPressed(NAME_UPBTN) ? "1" : "0");
	u8g2.print(buttonIsPressed(NAME_LEFTBTN) ? "1" : "0");
	u8g2.print(buttonIsPressed(NAME_CENTERBTN) ? "1" : "0");
	u8g2.print(buttonIsPressed(NAME_RIGHTBTN) ? "1" : "0");
	u8g2.print(buttonIsPressed(NAME_DOWNBTN) ? "1" : "0");
};

void switchToNextLine()
{
	y += 9;
	u8g2.setCursor(0, y);
};

void printRight(String text)
{
	u8g2.setCursor(128 - u8g2.getStrWidth(text.c_str()), y);
	u8g2.print(text);
};