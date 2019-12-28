#include "Map.h"
#include <stdlib.h>
#include "ConsoleDrawEngine.h"

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;
	map = new char[width * height];
	colors = new WORD[width * height];

	for (int i = 0; i < width * height; i++) {
		if (rand() % 10 > 8) {
			map[i] = ';';
			colors[i] = BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		}
		else if (rand() % 10 > 6) {
			map[i] = '.';
			colors[i] = BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		}
		else if (rand() % 10 > 5) {
			map[i] = '#';
			colors[i] = FOREGROUND_WHITE;
		}
		else {
			map[i] = ' ';
			colors[i] = BACKGROUND_GREEN;
		}
	}
}

Map::~Map() {
	delete map;
	delete colors;
}

char Map::GetTile(int x, int y) {
	if (y * width + x < 0 || y * width + x > width* height)
		return ' ';
	return map[y * width + x];
}

WORD Map::GetColor(int x, int y) {
	if (y * width + x < 0 || y * width + x > width* height)
		return 0x00;
	return colors[y * width + x];
}