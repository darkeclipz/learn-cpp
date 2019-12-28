#pragma once
#include <string>
#include "ConsoleDrawEngine.h"

struct vec2 {
	float x;
	float y;
};

class dynamic
{
private:
	std::string name;
	char symbol;
	char colour;
	vec2 position;


public:
	virtual void draw_self(ConsoleDrawEngine* cde);
	virtual void tick(float fTimeElapsed);
	virtual void interact(dynamic* d);
};

class player : dynamic { };
class monster : dynamic { };
class teleport : dynamic { };
class item : dynamic { };

