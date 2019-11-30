// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void read_file() {
	std::ifstream file("file.txt");
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			std::cout << line.c_str() << '\n';
			//printf("%s", line.c_str());
		}
		file.close();
	}
}

std::string get_hello() {
	return "Hello world!";
}

int *get_array() {
	int foo[5] = { 1, 2, 3, 4, 5 };
	return foo;
}

int main()
{
    std::cout << "Hello World!\n";
	read_file();

	std::cout << "Enter an integer: ";
	int num{ 0 };
	std::cin >> num;

	std::cout << "Double the number is: " << num * 2 << '\n';

	std::cout << get_hello();

	auto my_str = get_hello();
	int len = my_str.length();
	for (int i = 0; i < len; i++) {
		std::cout << my_str[i] << '\n';
	}

	std::cout << get_array()[0];

	return 0;
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
