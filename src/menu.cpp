#include "gameEngine.h"

void menuSetup() {

};

int selectedOption = 0;

String gameMenuOptionsStrings[] = {
	"Pong",
	"Snake",
  "Exit"
};
enum GameMenuOptions{
	gamemenuoption_PONG,
  gamemenuoption_SNAKE,
	gamemenuoption_EXIT
};

bool menuLoop()
{

	u8g2.setFont(u8g2_font_6x13_mf);
	u8g2.setDrawColor(1);
	u8g2.drawBox(0, 0, 128, 10);
	u8g2.setDrawColor(0);
	printCenter("Menu", 10);
	u8g2.setDrawColor(1);

	if(!digitalRead(LEFTBTN)){
		runningGame = GAME_PONG;
	}
	if(!digitalRead(RIGHTBTN)){
		runningGame = GAME_SNAKE;
	}
	return true;
}