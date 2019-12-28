#include "ConsoleDrawEngine.h"
#include "iostream";
#include "vector";

ConsoleDrawEngine::ConsoleDrawEngine(short width, short height, std::string title) {
	this->width = width;
	this->height = height;
	this->title = title;
	this->windowSize = { 0, 0, width - 1, height - 1 };
	this->bufferSize = { width, height };
	this->characterBufferSize = { width, height };
	this->characterBufferPosition = { 0, 0 };
	this->consoleWriteArea = { 0, 0, width - 1, height - 1 };
	this->consoleBuffer = new CHAR_INFO[width * height];
	this->wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	this->rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	SetConsoleCursorPosition(wHnd, { 0, height - 1 });
	SetConsoleTitle(title.c_str());
	ClearBuffer();
}

ConsoleDrawEngine::~ConsoleDrawEngine() {
	delete consoleBuffer;
}

void ConsoleDrawEngine::ClearBuffer() {
	for (int i = 0; i < width * height; i++) {
		consoleBuffer[i].Char.AsciiChar = 0x00;
		consoleBuffer[i].Attributes = 0x00;
	}
}

void ConsoleDrawEngine::DrawBuffer() {
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterBufferPosition, &consoleWriteArea);
}

void ConsoleDrawEngine::DrawString(int x, int y, std::string text, WORD attributes = FOREGROUND_WHITE) {
	COORD pos = { x, y };
	for (int i = 0; i < text.size(); i++) {
		COORD rpos = { (short)pos.X + (short)i, (short)pos.Y };
		SetAttribute(rpos.X, rpos.Y, attributes);
		SetChar(rpos.X, rpos.Y, text[i]);
	}
}

void ConsoleDrawEngine::SetChar(int x, int y, char c) {
	COORD pos = { x, y };
	if (pos.X + width * pos.Y < 0 || pos.X + width * pos.Y >= width * height)
		return;
	this->consoleBuffer[pos.X + width * pos.Y].Char.AsciiChar = c;
}

void ConsoleDrawEngine::SetAttribute(int x, int y, WORD attributes) {
	COORD pos = { x, y };
	if (pos.X + width * pos.Y < 0 || pos.X + width * pos.Y >= width * height)
		return;
	this->consoleBuffer[pos.X + width * pos.Y].Attributes = attributes;
}

int ConsoleDrawEngine::GetWidth() {
	return width;
}

int ConsoleDrawEngine::GetHeight() {
	return height;
}