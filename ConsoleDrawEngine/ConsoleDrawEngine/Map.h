#pragma once
#include <windows.h>

class Map
{
private:
	char* map;
	WORD* colors;
	int width;
	int height;
public:
	Map(int width, int height);
	~Map();
	char GetTile(int x, int y);
	WORD GetColor(int x, int y);
};

