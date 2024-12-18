#include "button.h"
#include "snake.h"
#include "fruit.h"
#include "renderer.h"
#include "snake-game.h"
//#include "games/snake/button.h"
#include "buttons.h"

Snake snake;
Fruit fruit(&snake);

void snakeSetup()
{

	Renderer::initialize();
	snake = Snake();
	fruit = Fruit(&snake);
}

void snakeLoop()
{
	if (buttonIsPressed(NAME_UPBTN))
		snake.turn(UP);
	if (buttonIsPressed(NAME_DOWNBTN))
		snake.turn(DOWN);
	if (buttonIsPressed(NAME_LEFTBTN))
		snake.turn(LEFT);
	if (buttonIsPressed(NAME_RIGHTBTN))
		snake.turn(RIGHT);

	bool resetFruit = false;
	if (snake.nextHeadPosition() == fruit.getPosition())
	{
		snake.grow();
		resetFruit = true;
	}

	snake.advance();
	if (resetFruit)
		fruit.randomize(&snake);

	Renderer::startFrame();
	Renderer::renderBorder();
	Renderer::renderSnake(&snake);
	Renderer::renderFruit(&fruit);
	if (!snake.isAlive()){
		Renderer::renderGameOver(&snake);
		snakeSetup();
	}
	Renderer::endFrame();

	delay(150);
}
