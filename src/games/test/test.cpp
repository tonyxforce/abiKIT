#include "test.h"

void testSetup() {

};

int y = 0;
uint8_t a = 0;
void switchToNextLine();

void testLoop()
{
	CRGB::HTMLColorCode color = !digitalRead(UPBTN) ? CRGB::Red : !digitalRead(LEFTBTN) ? CRGB::Green
																														: !digitalRead(CENTERBTN) ? CRGB::Blue
																														: !digitalRead(RIGHTBTN)	? CRGB::White
																														: !digitalRead(DOWNBTN)		? CRGB::Yellow
																																											: CRGB::Black;
	fillLeds(color);

	switch (color)
	{
	case CRGB::Red:
		beep(200, (1000 / fps) - 50, BEEPTYPE_GAME);
		break;
	case CRGB::Green:
		beep(400, (1000 / fps) - 50, BEEPTYPE_GAME);
		break;
	case CRGB::Blue:
		beep(600, (1000 / fps) - 50, BEEPTYPE_GAME);
		break;
	case CRGB::White:
		beep(800, (1000 / fps) - 50, BEEPTYPE_GAME);
		break;
	case CRGB::Yellow:
		beep(1000, (1000 / fps) - 50, BEEPTYPE_GAME);
		break;
	}

	y = 9;
	u8g2.setFont(u8g2_font_6x13_mf);

	u8g2.print(digitalRead(UPBTN) ? "Fel ki" : "Fel be");
	switchToNextLine();
	u8g2.print(digitalRead(LEFTBTN) ? "Bal ki" : "Bal be");
	switchToNextLine();
	u8g2.print(digitalRead(CENTERBTN) ? "Kozep ki" : "Kozep be");
	switchToNextLine();
	u8g2.print(digitalRead(RIGHTBTN) ? "Jobb ki" : "Jobb be");
	switchToNextLine();
	u8g2.print(digitalRead(DOWNBTN) ? "Le ki" : "Le be");
	switchToNextLine();

	a++;
	u8g2.print(a);

	switchToNextLine();
	u8g2.print((1000 / fps) - 50);
};

void switchToNextLine()
{
	y += 9;
	u8g2.setCursor(0, y);
};