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

void add(int index, std::vector<Token>& tokens) {
	tokens[index - 1].value = tokens[index - 1].value + tokens[index + 1].value;
	tokens.erase(tokens.begin() + index, tokens.begin() + index + 2);
}

void sub(int index, std::vector<Token>& tokens) {
	tokens[index - 1].value = tokens[index - 1].value - tokens[index + 1].value;
	tokens.erase(tokens.begin() + index, tokens.begin() + index + 2);
}

void mult(int index, std::vector<Token>& tokens) {
	tokens[index - 1].value = tokens[index - 1].value * tokens[index + 1].value;
	tokens.erase(tokens.begin() + index, tokens.begin() + index + 2);
}

void div(int index, std::vector<Token>& tokens) {
	tokens[index - 1].value = tokens[index - 1].value / tokens[index + 1].value;
	tokens.erase(tokens.begin() + index, tokens.begin() + index + 2);
}

void pass_mult_div(std::vector<Token>& tokens) {
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].kind == '*') mult(i--, tokens);
		if (tokens[i].kind == '/') div(i--, tokens);
	}
}

void pass_add_sub(std::vector<Token>& tokens) {
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].kind == '+') add(i--, tokens);
		if (tokens[i].kind == '-') sub(i--, tokens);
	}
}

void pass_parenthesis(std::vector<Token>& tokens) {
	
	bool reset = false;		// Re-evaluate everything.
	int left_index = 0;		// Index of the last ( parenthesis.
	int right_index = 0;	// Index of the first ) parenthesis.

	for (int i = 0; i < tokens.size(); i++) {

		if (reset) {
			i = 0;
			reset = false;
			right_index = 0;
		}

		if (tokens[i].kind == '(') left_index  = i;
		if (tokens[i].kind == ')') right_index = i;
		
		if (right_index > 0) {
			std::vector<Token> sub_expression(tokens.begin() + left_index + 1, tokens.begin() + right_index );
			pass_mult_div(sub_expression);
			pass_add_sub(sub_expression);
			tokens[left_index].value = sub_expression[0].value;
			tokens[left_index].kind = '8';
			tokens.erase(tokens.begin() + left_index + 1, tokens.begin() + right_index + 1);
			reset = true;
		}
	}
}

void evaluate() {
	pass_parenthesis(tokens);
	pass_mult_div(tokens);
	pass_add_sub(tokens);
	std::cout << "Result: " << tokens[0].value << '\n';
	tokens.erase(tokens.begin(), tokens.end());
}

int main()
{
	try {

		bool quit = false;

		std::cout << "Simple expression parser\nSupported operations: +, -, *, / \nUse ';' to evaluate, and 'q' to quit.\n";

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


