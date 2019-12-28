#include <string>
#include <vector>
#include <windows.h>
#include "../ConsoleDrawEngine/ConsoleDrawEngine.cpp"
//#include "cgeExample.cpp"

int main() {

	std::vector<std::string> story{
		"Hello world!",
		"This text in the console of this c++ app",
		"is displayed by using buffers.",
		"Later on, this will enable us to draw",
		"interesting things."
	};

	ConsoleDrawEngine engine(120, 40, "Console");
	int s = 0;

	engine.SetChar({ 5, 5 }, 'q');
	engine.SetAttribute({ 5, 5 }, 0x01);

	engine.DrawText({ 5, 6 }, "Hello world!", 0x02);

	engine.DrawBuffer();


	while (true) {
		engine.ClearBuffer();
		engine.DrawText({ 5, 5 }, story[s++ % story.size()], FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		engine.DrawBuffer();
		Sleep(1500);
	}

	getchar();
}