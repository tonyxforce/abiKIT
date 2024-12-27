#include "breakout.h"

const int rowCount = 4;
const int blockCount = (DISPLAYW / 16) * (rowCount);

bool blocks[blockCount];
int blocksPos[blockCount][2];

#define ISBETWEEN(x, min, max) (((x) >= (min)) && ((x) <= (max)))

float breakoutBounceX(float x)
{
	float newX = random(2000, 3001) / 1000;
	return x > 0 ? -newX : newX;
};
float breakoutBounceY(float y)
{
	float newY = random(2000, 3001) / 1000;
	return y > 0 ? -newY : newY;
};

void breakoutSetup()
{
	paddleX = 0;

	ballX = 64;
	ballY = 32;

	ballVelX = 3;
	ballVelY = 3;

	lastUserInput = millis();
	int i = 0;
	for (int row = 0; row < rowCount; row++)
	{
		for (int col = 0; col < DISPLAYW; col += 16)
		{
			int x = col + ((row & 1) * 8);
			if (128 - x > 14)
			{
				i++;
				blocks[i] = true;
				blocksPos[i][0] = x;
				blocksPos[i][1] = row * 5;
			}
		}
	}
};

void updateBreakout()
{
	paddleX = constrain(paddleX, 0, 128 - 16);

	if (ballY >= DISPLAYH - 2 && ballX >= paddleX && ballX <= paddleX + 16)
	{
		ballVelY = breakoutBounceY(ballVelY);
	}

	if (ballY - 2 <= 0)
		ballVelY = breakoutBounceY(ballVelY);

	if (ballY - 2 >= DISPLAYH)
	{
		ballY = 32;
		ballVelX = breakoutBounceY(ballVelX);
	}

	if (ballX - 2 <= 0 || ballX + 2 >= DISPLAYW)
		ballVelX = breakoutBounceY(ballVelX);

	ballX += ballVelX;
	ballY += ballVelY;

	if (millis() - lastUserInput > 5000)
	{
		paddleX = ballX - 8;
	}

	paddleX = constrain(paddleX, 0, 128 - 16);

	for (int i = 0; i < blockCount; i++)
	{
		if (!blocks[i])
			continue;
		int x = blocksPos[i][0];
		int y = blocksPos[i][1];
		if (ISBETWEEN(ballX, x, x + 16) && ISBETWEEN(ballY, y, y + 4))
		{
			blocks[i] = false;
			ballVelX = breakoutBounceY(ballVelX);
			ballVelY = breakoutBounceY(ballVelY);
		}
	}
}

void drawBreakout()
{
	for (int i = 0; i < blockCount; i++)
	{
		if (blocks[i])
		{
			int x = blocksPos[i][0];
			int y = blocksPos[i][1];
			u8g2.drawBox(x, y, 15, 4);
		}
	}

	u8g2.drawBox(paddleX, 64 - 2, 16, 2);
	u8g2.drawDisc(ballX, ballY, 2);
}

bool breakoutLoop()
{
	if (RIGHTPressed())
	{
		paddleX += 5.5;
		lastUserInput = millis();
	}
	if (LEFTPressed())
	{
		paddleX -= 5.5;
		lastUserInput = millis();
	}
	updateBreakout();
	drawBreakout();
	return true;
};