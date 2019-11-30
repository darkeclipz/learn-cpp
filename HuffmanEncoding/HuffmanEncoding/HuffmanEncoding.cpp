// HuffmanEncoding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <string>
#include <map>

template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B>& p)
{
	return std::pair<B, A>(p.second, p.first);
}

// flips an associative container of A,B pairs to B,A pairs
template<typename A, typename B, template<class, class, class...> class M, class... Args>
std::multimap<B, A> flip_map(const M<A, B, Args...>& src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(),
		std::inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}

int get_mode(std::string arg) {
	if      (arg == "-encode") return 0;
	else if (arg == "-decode") return 1;
	throw std::invalid_argument("Mode must be specified with either -encode or -decode.");
}

std::string get_file_name(std::string arg) {
	if (arg.length() == 0)
		throw std::invalid_argument("File name must be specified after -encode or -decode.");
	return arg;
}

void read_file(std::string file_path) {
	std::ifstream file(file_path);
	if (file.is_open()) {
		std::string line;
		std::cout << "\nFile contents:\n";
		while (getline(file, line)) {
			std::cout << line << '\n';
		}
		file.close();
	}
}

void f() {
	std::cout << "f()";
	return;
}

void encode(std::string file_path) {
	// Read file contents 
	std::map<char, int> characters;
	std::ifstream file(file_path);
	if (file.is_open()) {
		std::string line;
		std::cout << "\nFile contents:\n";
		while (getline(file, line)) {
			std::cout << line << '\n';
			for (int i = 0; i < line.length(); i++) {
				characters[line[i]]++;
			}
		}
		file.close();
	}

	flip_map(characters);

	std::map<char, int>::iterator it;
	for (it = characters.begin(); it != characters.end(); it++) {
		std::cout << it->first
			<< '='
			<< it->second
			<< std::endl;
	}

	// Count letter occurances
	// Create a binary tree based on the occurance
	// Open output file
	// Encode the characters and write to file
	// Encode the binary tree and write and end of file
	// Close output file
}

void decode(std::string file_path) {
	// Open file
	// Decode the binary tree at the end of the file
	// Decode all the characters and write to file
	// Close the output file
}

int main(int argc, char *argv[], char* envp[]) {

	int mode = get_mode(argv[1]);
	std::cout << "Mode = " << mode << '\n';

	std::string file_name = get_file_name(argv[2]);
	std::cout << "File = " << file_name << '\n';

	switch (mode) {
	case 0: encode(file_name); break;
	case 1: decode(file_name); break;
	default:
		throw std::invalid_argument("Mode not supported, please use -encode or -decode only.");
	}

	return 0;
}
