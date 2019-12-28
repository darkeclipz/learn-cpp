// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ConsoleScreen.h"

const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 40;
ConsoleScreen gfx(120, 40, "Game of Life");
bool bExit = false;
const int ALIVE = GREEN;
const int DEAD = 0;

int count_neighbours(int x, int y) {
	if (x <= 0 || y <= 0) {
		return 0;
	}
	int count = 0;
	for (int i = x - 1; i < x + 1; i++) {
		for (int j = y - 1; j < y + 1; j++) {
			count += gfx.GetAttribute(i, j) > 0 && !(i == x && j == y) ? 1 : 0;
		}
	}
	return count;
}

void draw_loop() {
	gfx.ClearBuffer();
	for (int x = 0; x < SCREEN_WIDTH; x++) {
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			switch (count_neighbours(x, y)) {
			case 0: case 1:
				gfx.SetAttribute(x, y, DEAD);
				break;
			case 2: break;
			case 3:
				gfx.SetAttribute(x, y, ALIVE);
				break;
			default:
				gfx.SetAttribute(x, y, DEAD);
				break;
			}
		}
	}
	gfx.SetAttribute(0, 0, ALIVE);
	gfx.DrawBuffer();
}

void glider(ConsoleScreen& cs, int x, int y) {
	cs.SetAttribute(x,		y,		ALIVE);
	cs.SetAttribute(x + 1,	y + 1,	ALIVE);
	cs.SetAttribute(x + 2,	y + 1,	ALIVE);
	cs.SetAttribute(x,		y + 2,	ALIVE);
	cs.SetAttribute(x + 1,	y + 2,	ALIVE);
}

int main()
{
	glider(gfx, 25, 25);
	do draw_loop(); 
	while(!bExit);
}

