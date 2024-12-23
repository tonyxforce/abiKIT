#include "breakout.h"


void breakoutSetup() {
paddleX = 0;


ballX = 64;
ballY = 32;

ballVelX = 3;
ballVelY = 3;

lastUserInput = millis();
};

void updateBreakout(){
	if(RIGHTPressed()){
		paddleX += 4;
	}
	if(LEFTPressed()){
		paddleX -= 4;
	}
	paddleX = constrain(paddleX, 0, 128-16);

}

void drawBreakout(){
u8g2.drawBox(paddleX, 64-2, 16, 2);
}

bool breakoutLoop() {
updateBreakout();
drawBreakout();
return millis()-lastUserInput<5000;
};