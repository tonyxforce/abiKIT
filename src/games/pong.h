#ifndef PONG_H
#define PONG_H

extern int paddle1Y, paddle2Y;
extern int ballX, ballY;
extern int ballVelX, ballVelY;

void handleButtons();
void updateGame();
void drawGame();
void sendGameState();
void receivePaddlePosition();

#endif