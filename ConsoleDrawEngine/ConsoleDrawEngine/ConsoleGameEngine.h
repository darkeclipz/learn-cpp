#pragma once
#include "ConsoleDrawEngine.h"
#include "Map.h"

class ConsoleGameEngine
{
private:
	ConsoleDrawEngine* cde;
	double time;
	Map* map;
public:
	ConsoleGameEngine(ConsoleDrawEngine* cde);
	~ConsoleGameEngine();
	void Run();
	void OnUpdate(double fTimeElapsed);
	void OnDraw(double fTimeElapsed);
	void DrawMap();
};

