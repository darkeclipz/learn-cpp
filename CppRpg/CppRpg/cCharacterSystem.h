#pragma once
#include <vector>
#include <string>

struct character
{
	std::string name;
};

class CharacterSystem
{
protected:
	std::vector<character> characters;
public:
	CharacterSystem();
	~CharacterSystem();
public:
	int size();
	character create_character(std::string name);
	character get_character(int id);
};