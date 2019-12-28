#include "ConsoleDrawEngine.h"
#include "ConsoleGameEngine.h"

const int CONSOLE_WIDTH = 120;
const int CONSOLE_HEIGHT = 40;
const std::string CONSOLE_TITLE = "Console Drawing Engine";

int main() {
	ConsoleDrawEngine cde(CONSOLE_WIDTH, CONSOLE_HEIGHT, CONSOLE_TITLE);
	ConsoleGameEngine cge(&cde);
	cge.Run();
}