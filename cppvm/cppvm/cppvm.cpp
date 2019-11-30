// cppvm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> load_rom(std::string file_path) 
{
	std::ifstream ifs(file_path.c_str(), std::ios_base::binary);
	//if (!ifs) throw std::invalid_argument("can't open rom.");
	std::vector<int> bin;
	char* c = 0x0;
	while (ifs.read(c, sizeof(c)))
		bin.push_back((int)c);
	return bin;
}

int main(int argc, char* argv[], char* envp[])
{
	std::string rom_path = argv[1];
	std::vector<int> rom = load_rom(rom_path);

	for (int c : rom) {
		std::cout << c;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
