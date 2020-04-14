#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
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
	virtual ~Parser() { };
	// Parser(Parser const & other) =delete;
	// Parser & operator=(Parser const & rhs) =delete;

	std::queue<Instruction> source();

	void error(TokenError const & e);

private:
	bool verify(Token::Type type); // get next token if types match
	void assert(Token::Type type); // same but raise an exception in case they don't
	Instruction instr();
	std::array<std::string, 2> value();

	std::string file_;
	std::stringstream source_;
	Token token_;
};

#endif // PARSER_H_
