#include "cCharacterSystem.h"
#include <iostream>

CharacterSystem::CharacterSystem()
{
	
}

character CharacterSystem::create_character(std::string name) 
{
	character c { name };
	this->characters.push_back(c);
	return c;
}

int CharacterSystem::size()
{
	return this->characters.size();
}

character CharacterSystem::get_character(int id)
{
	return this->characters[id];
}