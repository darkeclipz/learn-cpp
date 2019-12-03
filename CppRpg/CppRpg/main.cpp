#include <iostream>
#include <vector>
#include "states.h"
#include "cMainMenu.h"
#include <windows.h>
#include "cCharacterSystem.h"

state currentState = state::MENU;
MainMenu* mainMenu;
CharacterSystem* characterSystem;

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void init() 
{
	characterSystem = new CharacterSystem();
	mainMenu = new MainMenu(characterSystem);
}

void destroy()
{
	delete mainMenu;
	delete characterSystem;
}

void handle_state()
{
	switch (currentState)
	{
	case state::MENU:				
		currentState = mainMenu->main();			
		break;
	case state::CHARACTER_MENU:		
		currentState = mainMenu->characters();
		break;
	case state::CREATE_CHARACTER:	
		currentState = mainMenu->create_character();
		break;
	default:
		throw std::invalid_argument("invalid state.");
	}

	clear();
}

int main() 
{
	init();
	while (currentState != state::QUIT)
		handle_state();
	destroy();
	return 0;
}