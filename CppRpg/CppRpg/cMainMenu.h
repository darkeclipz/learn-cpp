#pragma once
#include "states.h"
#include "cCharacterSystem.h"

class MainMenu
{
private:
	CharacterSystem* characterSystem;
public:
	MainMenu(CharacterSystem* cs);
	~MainMenu();
public:
	state main();
	state characters();
	state create_character();
};