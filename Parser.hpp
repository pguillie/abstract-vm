#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <array>
#include <string>

#include "Lexer.hpp"

struct Instruction {
	std::string action;
	std::vector<std::array<std::string, 2>> value;
};

class Parser {
public:
	Parser(Lexer & lexer);
	virtual ~Parser() { };
	// Parser(Parser const & other) =delete;
	// Parser & operator=(Parser const & rhs) =delete;

	std::queue<Instruction> source();
	Instruction instr_line();

private:
	Lexer & lexer_;
	Token token_;
};

#endif // PARSER_H_
