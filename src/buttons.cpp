#include "buttons.h"

bool buttonsSetup(){
pinMode(UPBTN, INPUT_PULLUP);
pinMode(LEFTBTN, INPUT_PULLUP);
pinMode(CENTERBTN, INPUT_PULLUP);
pinMode(RIGHTBTN, INPUT_PULLUP);
pinMode(DOWNBTN, INPUT_PULLUP);

return true;
};

void buttonsLoop(bool& up, bool& left, bool& center, bool& right, bool& down){
up = !digitalRead(UPBTN);
left = !digitalRead(LEFTBTN);
center = !digitalRead(CENTERBTN);
right = !digitalRead(RIGHTBTN);
down = !digitalRead(DOWNBTN);
};