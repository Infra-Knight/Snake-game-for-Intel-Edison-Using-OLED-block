#include <iostream>
#include "oled/Edison_OLED.h"
#include "gpio/gpio.h"
#include "math.h"
//#include <unistd.h> // for usleep
#include <stdlib.h> // Gives us atoi
#include <stdio.h>

using namespace std;

bool gameOver;
int x, y, foodX, foodY;
int tailX[64 * 48], tailY[64 * 48];
int nTail;
int score = 0;

enum eDirection{STOP = 0, LEFT,RIGHT,UP,DOWN};
eDirection dir;

void setupOLED();
void Setup();
void cleanUp();
void Draw();
void Input();

edOLED oled;

gpio BUTTON_UP(47, INPUT);
gpio BUTTON_DOWN(44, INPUT);
gpio BUTTON_LEFT(165, INPUT);
gpio BUTTON_RIGHT(45, INPUT);
gpio BUTTON_SELECT(48, INPUT);
gpio BUTTON_A(49, INPUT);
gpio BUTTON_B(46, INPUT);

void setupOLED()
{
	oled.begin();
	oled.clear(PAGE);
	oled.display();
	oled.setFontType(0);
}

void Setup() {
	gameOver = false;
	dir = STOP;
	x = LCDWIDTH / 2;
	y = LCDHEIGHT / 2;
	foodX = rand() % LCDWIDTH;
	foodY = rand() % LCDHEIGHT;
}

void Draw() {
	oled.clear(PAGE);
	oled.circle(foodX, foodY,2);
	oled.pixel(x, y);
	for (int i = 0; i < LCDHEIGHT; i++)
	{
		for (int j = 0; j < LCDWIDTH; j++)
		{
			for (int k = 0; k < nTail; k++) {
				if (tailX[k] == j && tailY[k]==i ) {
					oled.pixel(j, i);
				}
			}
		}
	}
	oled.display();
}

void Input() {
	if (BUTTON_UP.pinRead() == LOW)
	{
		dir = UP;
	}
	if (BUTTON_DOWN.pinRead() == LOW)
	{
		dir = DOWN;
	}
	if (BUTTON_LEFT.pinRead() == LOW)
	{
		dir = LEFT;
	}
	if (BUTTON_RIGHT.pinRead() == LOW)
	{
		dir = RIGHT;
	}
	if (BUTTON_A.pinRead()==LOW) {
		gameOver = true;
	}
}

int Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prevX2, prevY2;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prevX2 = tailX[i];
		prevY2 = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevX2;
		prevY = prevY2;
	}


	switch (dir) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	}
	/*if (x > LCDWIDTH || x < 0 || y>LCDHEIGHT || y<0) {
		gameOver = true;
	}*/
	if (x > LCDWIDTH) x = 0; else if (x < 0) x = LCDWIDTH - 1;
	if (y > LCDHEIGHT) y = 0; else if (y < 0) y = LCDHEIGHT - 1;

	for (int i = 0; i < nTail;i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}

	if (x == foodX -1 && y == foodY -2) {
		score++;
		foodX = rand() % 64;
		foodY = rand() % 48;

	}
	if (x == foodX    && y == foodY -2) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX +1 && y == foodY -2) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX +2 && y == foodY -1) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX +2 && y == foodY   ) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX +2 && y == foodY +1) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX -1 && y == foodY +2) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX    && y == foodY +2) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX +1 && y == foodY +2) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX -2 && y == foodY -1) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX -2 && y == foodY   ) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}
	if (x == foodX -2 && y == foodY +1) {
		score++;
		nTail++;
		foodX = rand() % 64;
		foodY = rand() % 48;
	}

	if (nTail == LCDWIDTH * LCDHEIGHT-1) {
		gameOver = true;
	}
}

void drawScore(int a)
{
	oled.clear(PAGE);
	oled.setCursor(LCDWIDTH/2,LCDHEIGHT/ 2);
	oled.print(a);
	oled.display();
}

void cleanUp()
{
	oled.clear(PAGE);
	oled.display();
}

int main() {
	setupOLED();
	Setup();
	while (gameOver == false) {
		Draw();
		Input();
		Logic();
	}
	drawScore(score);
}