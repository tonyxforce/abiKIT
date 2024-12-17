#include "button.h"
#include "snake.h"
#include "fruit.h"
#include "renderer.h"
#include "snake-game.h"

Snake snake;
Fruit fruit(&snake);

void snakeSetup() {
  Renderer::initialize();
	snake = Snake();
	fruit = Fruit(&snake);
}

void snakeLoop() {
  if (!digitalRead(UPBTN)) snake.turn(UP);
  if (!digitalRead(DOWNBTN)) snake.turn(DOWN);
  if (!digitalRead(LEFTBTN)) snake.turn(LEFT);
  if (!digitalRead(RIGHTBTN)) snake.turn(RIGHT);

  bool resetFruit = false;
  if(snake.nextHeadPosition() == fruit.getPosition()) {
    snake.grow();
    resetFruit = true;
  }

  snake.advance();
  if(resetFruit) fruit.randomize(&snake);
  
  Renderer::startFrame();
  Renderer::renderBorder();
  Renderer::renderSnake(&snake);
  Renderer::renderFruit(&fruit);
  if(!snake.isAlive()) Renderer::renderGameOver(&snake);
  Renderer::endFrame();
  
  delay(150);
}
