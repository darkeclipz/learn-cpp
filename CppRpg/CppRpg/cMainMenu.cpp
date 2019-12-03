#include "cMainMenu.h"
#include "iostream"
#include "states.h"
#include "cCharacterSystem.h"

MainMenu::MainMenu(CharacterSystem* cs)
{
	this->characterSystem = cs;
}

MainMenu::~MainMenu() { }

state MainMenu::main()
{
	std::cout << "MainMenu::main()\r\n";
	std::cout << "1) Characters\r\n";
	std::cout << "Q) Quit\r\n";
	char action;
	std::cin >> action;
	switch (action) {
	case '1': return state::CHARACTER_MENU; break;
	case 'q':
	case 'Q': return state::QUIT; break;
	default: return state::MENU;
	}
}

state MainMenu::characters()
{
	std::cout << "There are " << this->characterSystem->size() << " characters.\r\n";
	if (this->characterSystem->size() > 0) {
		for (int i = 0; i < this->characterSystem->size(); i++) {
			std::cout << i << ") " << this->characterSystem->get_character(i).name << "\r\n";
		}
		std::cout << std::endl;
	}
	std::cout << "N) Create new character\r\n";
	std::cout << "B) Back to menu\r\n";
	char action;
	std::cin >> action;
	switch (action) {
	case 'n':
	case 'N': return state::CREATE_CHARACTER; break;
	case 'b':
	case 'B': return state::MENU; break;
	default: return state::CHARACTER_MENU; break;
	}
}

state MainMenu::create_character()
{
	std::cout << "Create a new character\r\n";
	std::cout << "Enter a name: ";
	std::string name;
	std::cin >> name;
	this->characterSystem->create_character(name);
	return state::CHARACTER_MENU;
}
