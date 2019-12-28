#include "ConsoleGameEngine.h"
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

float playerPositionX = 0.0;
float playerPositionY = 0.0;

const int mapWidth = 120;
const int mapHeight = 40;

std::string format_float(double x, int precision = 2) {
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(precision) << x;
	return ss.str();
}

ConsoleGameEngine::ConsoleGameEngine(ConsoleDrawEngine* cde) {
	this->cde = cde;
	this->time = 0.0;
	this->map = new Map(mapWidth, mapHeight);
}

ConsoleGameEngine::~ConsoleGameEngine() {
	delete map;
}

void ConsoleGameEngine::OnUpdate(double fTimeElapsed) {
	float speed = 8;
	float x = playerPositionX;
	float y = playerPositionY;
	if (GetKeyState('W') & 0x8000) playerPositionY -= speed * fTimeElapsed;
	if (GetKeyState('S') & 0x8000) playerPositionY += speed * fTimeElapsed;
	if (GetKeyState('A') & 0x8000) playerPositionX -= speed * fTimeElapsed;
	if (GetKeyState('D') & 0x8000) playerPositionX += speed * fTimeElapsed;
	if (map->GetTile(playerPositionX, playerPositionY) == '#') {
		playerPositionX = x;
		playerPositionY = y;
	}
}

void ConsoleGameEngine::DrawMap() {
	int width = cde->GetWidth();
	int height = cde->GetHeight();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			cde->SetChar(x, y, map->GetTile(x, y));
			cde->SetAttribute(x, y, map->GetColor(x, y));
		}
	}

	// player
	cde->SetChar(playerPositionX, playerPositionY, 'P');
	cde->SetAttribute(playerPositionX, playerPositionY, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void ConsoleGameEngine::OnDraw(double fElapsedTime) {

	DrawMap();

	std::vector<std::string> story{
		"Hello world!",
		"This text in the console of this c++ app",
		"is displayed by using buffers.",
		"Later on, this will enable us to draw",
		"interesting things."
	};

	cde->DrawString(5, 5, story[int(this->time) % story.size()], FOREGROUND_WHITE);

	for (int k = 65; k < 65 + 26; k++)
		if (GetKeyState(k) & 0x8000) {
			cde->SetChar((short)k - 65, 1, (char)k);
			cde->SetAttribute((short)k - 65, 1, FOREGROUND_RED | BACKGROUND_BLUE);
		}

	std::string timeString = "Time: " + format_float(this->time, 2);
	cde->DrawString(cde->GetWidth() - timeString.size() - 2, 1, timeString, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void ConsoleGameEngine::Run() {

	double elapsedTime = 0.0;
	auto previousTime = std::chrono::high_resolution_clock::now();

	while (true) {

		// Update the time.
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = currentTime - previousTime;
		previousTime = currentTime;
		elapsedTime = elapsed.count();
		this->time += elapsedTime;
		
		// Draw loop.
		OnUpdate(elapsedTime);
		cde->ClearBuffer();
		OnDraw(elapsedTime);
		cde->DrawBuffer();
	}
}