#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <array>
#include <string>

#include "Token.hpp"
#include "Lexer.hpp"

struct Instruction {
	std::string action;
	std::vector<std::array<std::string, 2>> value;
};

class Parser {
public:
	Parser(char const * file);
	virtual ~Parser();
	// Parser(Parser const & other) =delete;
	// Parser & operator=(Parser const & rhs) =delete;

	std::queue<Instruction> source();

private:
	bool verify(Token::Type type); // get next token if types match
	void assert(Token::Type type); // same but raise an exception in case they don't
	Instruction instr();
	std::array<std::string, 2> value();

	std::stringstream source_;
	Lexer * lexer_;
	Token token_;
};

#endif // PARSER_H_
