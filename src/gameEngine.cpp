#include "gameEngine.h"
#include "games/pong.h"
#include "games/snake/snake-game.h"
#include "menu.h"

RunningGame runningGame = MENU;

bool gameLoop(){
	switch(runningGame){
		case MENU:
      return menuLoop();
      break;
    case PONG:
			pongLoop();
      return true;
      break;
    case SNAKE:
			snakeLoop();
      return true;
      break;
  }
}