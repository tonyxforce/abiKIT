#ifndef BUTTONS_H
#define BUTTONS_H

#define UPBTN 18
#define LEFTBTN 16
#define CENTERBTN 17
#define RIGHTBTN 23
#define DOWNBTN 19

enum ButtonName{
	NAME_UPBTN,
	NAME_LEFTBTN,
	NAME_CENTERBTN,
	NAME_RIGHTBTN,
	NAME_DOWNBTN,
};

bool buttonIsPressed(ButtonName button);
void checkButtons();

void buttonsLoop();

bool UPPressed();
bool LEFTPressed();
bool CENTERPressed();
bool RIGHTPressed();
bool DOWNPressed();
bool ALLPressed();

extern bool button1Pressed;
extern bool button2Pressed;
extern bool button3Pressed;
extern bool button4Pressed;
extern bool button5Pressed;

extern bool button1PressedBef;
extern bool button2PressedBef;
extern bool button3PressedBef;
extern bool button4PressedBef;
extern bool button5PressedBef;

extern bool button1Clicked;
extern bool button2Clicked;
extern bool button3Clicked;
extern bool button4Clicked;
extern bool button5Clicked;

extern bool button1Checked;
extern bool button2Checked;
extern bool button3Checked;
extern bool button4Checked;
extern bool button5Checked;

#endif