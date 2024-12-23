#include "buttons.h"
#include <Arduino.h>

bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;
bool button4Pressed = false;
bool button5Pressed = false;

bool button1PressedBef = false;
bool button2PressedBef = false;
bool button3PressedBef = false;
bool button4PressedBef = false;
bool button5PressedBef = false;

bool button1Clicked = false;
bool button2Clicked = false;
bool button3Clicked = false;
bool button4Clicked = false;
bool button5Clicked = false;

bool button1Checked = false;
bool button2Checked = false;
bool button3Checked = false;
bool button4Checked = false;
bool button5Checked = false;

bool buttonIsPressed(ButtonName button)
{
	switch (button)
	{
	case NAME_UPBTN:
		button1Checked = true;
		return button1Clicked;
		break;

	case NAME_LEFTBTN:
		button2Checked = true;
		return button2Clicked;
		break;

	case NAME_CENTERBTN:
		button3Checked = true;
		return button3Clicked;
		break;

	case NAME_RIGHTBTN:
		button4Checked = true;
		return button4Clicked;
		break;

	case NAME_DOWNBTN:
		button5Checked = true;
		return button5Clicked;
		break;
	default:
		return false;
	}
};

void checkButtons()
{
	if (button1Pressed != button1PressedBef)
	{
		button1PressedBef = button1Pressed;
		button1Clicked = button1Pressed;
	}
	if (button2Pressed != button2PressedBef)
	{
		button2PressedBef = button2Pressed;
		button2Clicked = button2Pressed;
	}
	if (button3Pressed != button3PressedBef)
	{
		button3PressedBef = button3Pressed;
		button3Clicked = button3Pressed;
	}
	if (button4Pressed != button4PressedBef)
	{
		button4PressedBef = button4Pressed;
		button4Clicked = button4Pressed;
	}
	if (button5Pressed != button5PressedBef)
	{
		button5PressedBef = button5Pressed;
		button5Clicked = button5Pressed;
	}

	if (button1Checked)
	{
		button1Checked = false;
		button1Clicked = false;
	}
	if (button2Checked)
	{
		button2Checked = false;
		button2Clicked = false;
	}
	if (button3Checked)
	{
		button3Checked = false;
		button3Clicked = false;
	}
	if (button4Checked)
	{
		button4Checked = false;
		button4Clicked = false;
	}
	if (button5Checked)
	{
		button5Checked = false;
		button5Clicked = false;
	}

	button1Pressed = !digitalRead(UPBTN);
	button2Pressed = !digitalRead(LEFTBTN);
	button3Pressed = !digitalRead(CENTERBTN);
	button4Pressed = !digitalRead(RIGHTBTN);
	button5Pressed = !digitalRead(DOWNBTN);
}
void buttonsLoop()
{
	if (button1Checked)
	{
		button1Checked = false;
		button1Clicked = false;
	}
	if (button2Checked)
	{
		button2Checked = false;
		button2Clicked = false;
	}
	if (button3Checked)
	{
		button3Checked = false;
		button3Clicked = false;
	}
	if (button4Checked)
	{
		button4Checked = false;
		button4Clicked = false;
	}
	if (button5Checked)
	{
		button5Checked = false;
		button5Clicked = false;
	}
}

bool UPPressed()
{
	checkButtons();
	return button1Pressed;
};
bool LEFTPressed()
{
	checkButtons();
	return button2Pressed;
};
bool CENTERPressed()
{
	checkButtons();
	return button3Pressed;
};
bool RIGHTPressed()
{
	checkButtons();
	return button4Pressed;
};
bool DOWNPressed()
{
	checkButtons();
	return button5Pressed;
};

bool ALLPressed()
{
	checkButtons();
	return button1Pressed && button2Pressed && button3Pressed && button4Pressed && button5Pressed;
}