// calculator-cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>

class Token {
public:
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0) { }
	Token(char ch, double val) : kind(ch), value(val) { }
};

class token_stream_error {
public:
	std::string message;
	token_stream_error(std::string msg) {
		message = msg;
	}
};

class Token_stream {
public:
	Token_stream();
	int index;
	Token get();
	void putback(Token t);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream() : full(false), buffer(0), index(0) { }

void Token_stream::putback(Token t) {

	if (full) throw token_stream_error("putback() into a full buffer");

	buffer = t;
	full = true;
}

Token Token_stream::get() {

	if (full) {
		full = false;
		return buffer;
	}

	char ch;
	std::cin >> ch;

	switch (ch) {
	case ';': // Print
	case 'q': // Quit
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		std::cin.putback(ch);
		double val;
		std::cin >> val;
		return Token('8', val);
	default:
		throw token_stream_error("Bad token");
	}
}

Token_stream stream;
std::vector<Token> tokens;

void evaluate() {
	std::cout << "There are " << tokens.size() << " tokens to evaluate!\n";

	// * and /
	for (int i = 0; i < tokens.size(); i++) {

		if (tokens[i].kind == '*') {
			tokens[i - 1].value = tokens[i - 1].value * tokens[i + 1].value;
			tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
			i--;
		}
		if (tokens[i].kind == '/') {
			tokens[i - 1].value = tokens[i - 1].value / tokens[i + 1].value;
			tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
			i--;
		}

		std::cout << "Precedence (*/), i=" << i << ": ";
		for (int j = 0; j < tokens.size(); j++) {
			if(tokens[j].kind == '8') std::cout << tokens[j].value;
			else					  std::cout << tokens[j].kind;
		}
		std::cout << '\n';
	}

	// + and -
	for (int i = 0; i < tokens.size(); i++) {

		if (tokens[i].kind == '+') {
			tokens[i - 1].value = tokens[i - 1].value + tokens[i + 1].value;
			tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
			i--;
		}
		if (tokens[i].kind == '-') {
			tokens[i - 1].value = tokens[i - 1].value - tokens[i + 1].value;
			tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
			i--;
		}

		std::cout << "Precedence (+-), i=" << i << ": ";
		for (int j = 0; j < tokens.size(); j++) {
			if (tokens[j].kind == '8') std::cout << tokens[j].value;
			else					  std::cout << tokens[j].kind;
		}
		std::cout << '\n';
	}

	std::cout << "Result: " << tokens[0].value << '\n';
	tokens.erase(tokens.begin(), tokens.end());
}

int main()
{
	try {
		
		
		bool quit = false;

		while (std::cin && !quit) {
			
			try {

				std::cout << "\r> ";
				Token t = stream.get();
				
				switch (t.kind) {
				case ';': evaluate();  break;
				case 'q': quit = true; break;
				default: 
					tokens.push_back(t);
				}

			}
			catch (token_stream_error& e) {
				std::cout << e.message << '\n';
			}
			
		}

		return 0;
	}
	catch (std::exception& e) {
		std::cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown exception!\n";
		return 2;
	}
}


