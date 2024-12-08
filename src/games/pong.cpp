#include "gameEngine.h"
#include "pong.h"
#include "network.h"
#include "leds.h"

int paddle1Y = 30, paddle2Y = 30;
int ballX = 64, ballY = 32;
int ballVelX = 1, ballVelY = 1;

int score1 = 0;
int score2 = 0;

bool player1Auto = false;
bool player2Auto = false;

unsigned long lastUserInput = 0;
unsigned long lastPacketTime = 0;

void handleButtons()
{
	if (digitalRead(UPBTN) == LOW)
	{
		lastUserInput = millis();
		paddle1Y -= 2;
		if (paddle1Y < 0)
			paddle1Y = 0;
	}
	if (digitalRead(DOWNBTN) == LOW)
	{
		lastUserInput = millis();
		paddle1Y += 2;
		if (paddle1Y > 48)
			paddle1Y = 48; // Limit paddle position
	}
	if (millis() - lastUserInput > 5000)
	{
		player1Auto = true;
		leds[0].r = 255;
		paddle1Y = constrain(ballY - 8, 0, 48);
	}
	else
	{
		player1Auto = false;
			leds[0].r = 0;
	}
}

void updateGame()
{
	ballX += ballVelX;
	ballY += ballVelY;

	// Ball collision with top/bottom
	if (ballY <= 0 || ballY >= 64)
		ballVelY = -ballVelY;

	// Ball collision with paddles
	if (ballX <= 4 && ballY >= paddle1Y && ballY <= paddle1Y + 16)
		ballVelX = -ballVelX;
	if (ballX >= 124 && ballY >= paddle2Y && ballY <= paddle2Y + 16)
		ballVelX = -ballVelX;

	// Ball out of bounds
	if (ballX <= 0 || ballX >= 128)
	{
		if (ballX <= 0)
			score2++;
		if (ballX >= 128)
			score1++;
		ballX = 64;
		ballY = 32;
	}
}

void drawGame()
{
	u8g2.drawBox(0, paddle1Y, 2, 16);		// Draw paddle 1
	u8g2.drawBox(126, paddle2Y, 2, 16); // Draw paddle 2
	u8g2.drawDisc(ballX, ballY, 2);			// Draw ball
	u8g2.drawBox(64, 0, 1, 64);
	if(!player1Auto && !player2Auto){
	// 2/6 2/3
	u8g2.setFont(u8g2_font_mystery_quest_24_tf);
	u8g2.setCursor(/*2/6 of 128*/ 43, /*2/3 of 64*/ 43 - 6);
	u8g2.print(score1);
	// 2/3-width 2/3
	u8g2.setCursor(/*2/3 of 128-width of a character*/ 85 - 8, /*2/3 of 64*/ 43 - 6);
	u8g2.print(score2);
	}
}

void sendGameState()
{
	String gameState = String(paddle1Y) + "," + String(ballX) + "," + String(ballY);

	// Convert the string to a byte array
	const char *gameStateCStr = gameState.c_str();
	udp.beginPacket(clientIP, localUdpPort);
	udp.write((const uint8_t *)gameStateCStr, strlen(gameStateCStr)); // Send game state to client
	udp.endPacket();
}

void receivePaddlePosition()
{
	int packetSize = udp.parsePacket();
	if (packetSize)
	{
		lastPacketTime = millis();
		leds[1].g = 255;
		ledsLoop();
		int len = udp.read(incomingPacket, 255);
		if (len > 0)
		{
			incomingPacket[len] = 0;
			paddle2Y = atoi(incomingPacket); // Get paddle 2 position from client
			clientIP = udp.remoteIP();			 // Get client IP address
		}
	}
	else if (millis() - lastPacketTime >= 500)
	{
		paddle2Y = constrain(ballY - 8, 0, 64 - 16);
		ledsLoop();
		player2Auto = true;
		leds[1].g = 0;
		leds[1].r = 255;
	}
	else
	{
		player2Auto = false;
		leds[1].r = 0;
	};
}