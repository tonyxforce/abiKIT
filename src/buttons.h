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
void buttonsLoop();

#endif