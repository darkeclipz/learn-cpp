#pragma once
#include <windows.h>
#include <string>
#include <stdio.h> /* standard input/output */
#include <stdlib.h> /* included for rand */

const WORD FOREGROUND_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

class ConsoleDrawEngine
{
private:
	int width;
	int height;
	std::string title;
	HANDLE wHnd;
	HANDLE rHnd;
	SMALL_RECT windowSize;
	COORD bufferSize;
	COORD characterBufferSize;
	COORD characterBufferPosition;
	SMALL_RECT consoleWriteArea;
	CHAR_INFO* consoleBuffer;
public:
	ConsoleDrawEngine(short width, short height, std::string title);
	~ConsoleDrawEngine();
	void DrawString(int x, int y, std::string text, WORD attributes);
	void SetChar(int x, int y, char c);
	void SetAttribute(int x, int y, WORD attributes);
	void DrawBuffer();
	void ClearBuffer();
	int GetWidth();
	int GetHeight();
};

