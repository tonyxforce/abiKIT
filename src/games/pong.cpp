#include "gameEngine.h"
#include "pong.h"
#include "network.h"
#include "leds.h"
#include "display.h"
#include "buttons.h"

void pongSetup()
{
	paddle1Y = 30;
	paddle2Y = 30;

	ballX = 64;
	ballY = 32;

	ballVelX = 3;
	ballVelY = 3;

	score1 = 0;
	score2 = 0;

	player1Auto = false;
	player2Auto = false;

	lastUserInput = millis();
	lastPacketTime = millis();
}

void handlePongButtons()
{
	if (!settings.oneHanded ? UPPressed() : CENTERPressed())
	{
		lastUserInput = millis();
		paddle1Y -= 4;
		if (paddle1Y < 0)
			paddle1Y = 0;
	}
	if (DOWNPressed())
	{
		lastUserInput = millis();
		paddle1Y += 4;
		if (paddle1Y > 48)
			paddle1Y = 48; // Limit paddle position
	}
	if (millis() - lastUserInput > 5000)
	{
		player1Auto = true;
		leds[0] = CRGB::Red;

		paddle1Y = constrain(ballY - 5, 0, 48);
	}
	else
	{
		if (millis() - lastUserInput > 2500)
		{
			leds[0] = CRGB::Blue;
		}else leds[0] = CRGB::Green;
		player1Auto = false;
		leds[0].r = 0;
	}
}

void updatePong()
{
	ballX += ballVelX;
	ballY += ballVelY;

	// Ball collision with top/bottom
	if (ballY <= 0 || ballY >= 64)
	{
		ballVelY = -ballVelY;
		beep(200, 50, BEEPTYPE_GAME);
	}

	// Ball collision with paddles
	if (ballX <= 4 && ballY >= paddle1Y && ballY <= paddle1Y + 16)
	{
		ballVelX = -ballVelX;
		beep(400, 50, BEEPTYPE_GAME);
		leds[3].blue = 255;
	}
	else
	{
		leds[3].blue = 0;
	}
	if (ballX >= 124 && ballY >= paddle2Y && ballY <= paddle2Y + 16)
	{
		ballVelX = -ballVelX;
		beep(400, 50, BEEPTYPE_GAME);
		leds[2].blue = 255;
	}
	else
	{
		leds[2].blue = 0;
	}

	// Ball out of bounds
	if (ballX <= 0 || ballX >= 128)
	{
		if (ballX <= 0)
		{
			score2++;
			if (score2 >= 99999)
				score2 = 0;
		}
		if (ballX >= 128)
		{
			score1++;
			if (score1 >= 99999)
				score1 = 0;
		}
		ballX = 64;
		ballY = 32;
		beep(200, 150, BEEPTYPE_GAME);
	}
}

void drawPong()
{
	u8g2.drawBox(0, paddle1Y, 2, 16);		// Draw paddle 1
	u8g2.drawBox(126, paddle2Y, 2, 16); // Draw paddle 2
	u8g2.drawDisc(ballX, ballY, 2);			// Draw ball
	u8g2.drawBox(64, 0, 1, 64);					// Draw center line

	leds[2].red = constrain(map(ballX - 64, 0, 64, 0, 255), 0, 255);
	leds[2].green = 255 - leds[2].red;
	leds[3].red = constrain(map(64 - ballX, 0, 64, 0, 255), 0, 255);
	leds[3].green = 255 - leds[3].red;

	if ((!player1Auto && !player2Auto))
	{
		u8g2.setFont(u8g2_font_t0_22_mn);

		u8g2.setCursor(/*2/6 of 128*/ 43, /*2/3 of 64*/ 43 - 6);
		u8g2.drawStr((64 + 5) /*  - u8g2.getStrWidth(String(score1).c_str()) */, 43 - 6, String(score1).c_str());

		u8g2.setCursor(/*2/3 of 128-width of a character*/ (64 - 5) - u8g2.getStrWidth(String(score2).c_str()), /*2/3 of 64*/ 43 - 6);
		u8g2.print(score2);
	}
	else if (player1Auto && player2Auto)
	{
		tempFps = targetFps;
		targetFps = 1000;
	}
	else
	{
		targetFps = max(tempFps, 30);
	}
	if (settings.debugMode)
	{
		u8g2.setFont(u8g2_font_4x6_mf);
		u8g2.setCursor(0, 16);
		u8g2.print(ballX);
		u8g2.print(" ");
		u8g2.print(ballY);
		u8g2.setCursor(0, 24);
		u8g2.print(paddle1Y);
		u8g2.print(" ");
		u8g2.print(paddle2Y);
	}
}

void sendPongState()
{
	String gameState = String(paddle1Y) + "," + String(ballX) + "," + String(ballY);

	// Convert the string to a byte array
	const char *gameStateCStr = gameState.c_str();
	udp.beginPacket(clientIP, localUdpPort);
	udp.write((const uint8_t *)gameStateCStr, strlen(gameStateCStr)); // Send game state to client
	udp.endPacket();
}

void receivePongPaddlePosition()
{
	int packetSize = udp.parsePacket();
	if (packetSize)
	{
		lastPacketTime = millis();
		leds[1].g = 255;
		leds[1].r = 0;
		ledsLoop();
		int len = udp.read(incomingPacket, 255);
		if (len > 0)
		{
			incomingPacket[len] = 0;
			paddle2Y = constrain(atoi(incomingPacket), 0, 48); // Get paddle 2 position from client
			clientIP = udp.remoteIP();												 // Get client IP address
		}
	}
	else if (millis() - lastPacketTime >= 800)
	{
		paddle2Y = constrain(ballY - 8, 0, 48);
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

void pongLoop()
{
	handlePongButtons();
	updatePong();
	drawPong();
	sendPongState();
	receivePongPaddlePosition();
}