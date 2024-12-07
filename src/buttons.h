#include <Arduino.h>

#ifndef BUTTONS_H
#define BUTTONS_H

#define UPBTN 18
#define LEFTBTN 16
#define CENTERBTN 17
#define RIGHTBTN 23
#define DOWNBTN 19

bool buttonsSetup();
void buttonsLoop(bool& up, bool& left, bool& center, bool& right, bool& down);

#endif