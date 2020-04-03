#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <array>
#include <string>

#include "Lexer.hpp"

class Parser {
public:
	Parser(Lexer & lexer);
	virtual ~Parser() {};
	// Parser(Parser const & other) =delete;
	// Parser & operator=(Parser const & rhs) =delete;

	struct Instruction {
		std::string name;
		std::vector<std::array<std::string, 2>> args;
	};

	std::queue<Instruction> parse();

private:
	Lexer & lexer_;
};

#endif // PARSER_H_
