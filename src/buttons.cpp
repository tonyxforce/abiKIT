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

bool button1JustPressed = false;
bool button2JustPressed = false;
bool button3JustPressed = false;
bool button4JustPressed = false;
bool button5JustPressed = false;

bool button1Checked = false;
bool button2Checked = false;
bool button3Checked = false;
bool button4Checked = false;
bool button5Checked = false;

bool buttonIsPressed(ButtonName button)
{
	bool res;
	switch (button)
	{
	case NAME_UPBTN:
		button1Checked = true;
		return button1JustPressed;
		break;

	case NAME_LEFTBTN:
		button2Checked = true;
		return button2JustPressed;
		break;

	case NAME_CENTERBTN:
		button3Checked = true;
		return button3JustPressed;
		break;

	case NAME_RIGHTBTN:
		button4Checked = true;
		return button4JustPressed;
		break;

	case NAME_DOWNBTN:
		button5Checked = true;
		return button5JustPressed;
		break;
	default:
		return false;
	}
};

void buttonsLoop()
{
	if (button1Checked)
	{
		button1Checked = false;
		button1JustPressed = false;
	}
	if (button2Checked)
	{
		button2Checked = false;
		button2JustPressed = false;
	}
	if (button3Checked)
	{
		button3Checked = false;
		button3JustPressed = false;
	}
	if (button4Checked)
	{
		button4Checked = false;
		button4JustPressed = false;
	}
	if (button5Checked)
	{
		button5Checked = false;
		button5JustPressed = false;
	}

	button1Pressed = !digitalRead(UPBTN);
	button2Pressed = !digitalRead(LEFTBTN);
	button3Pressed = !digitalRead(CENTERBTN);
	button4Pressed = !digitalRead(RIGHTBTN);
	button5Pressed = !digitalRead(DOWNBTN);
	
	if (button1Pressed != button1PressedBef)
	{
		button1PressedBef = button1Pressed;
		button1JustPressed = button1Pressed;
	}
	if (button2Pressed != button2PressedBef)
	{
		button2PressedBef = button2Pressed;
		button2JustPressed = button2Pressed;
	}
	if (button3Pressed != button3PressedBef)
	{
		button3PressedBef = button3Pressed;
		button3JustPressed = button3Pressed;
	}
	if (button4Pressed != button4PressedBef)
	{
		button4PressedBef = button4Pressed;
		button4JustPressed = button4Pressed;
	}
	if (button5Pressed != button5PressedBef)
	{
		button5PressedBef = button5Pressed;
		button5JustPressed = button5Pressed;
	}

}