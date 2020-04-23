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

class SyntaxErr: public virtual TokErr {
public:
	SyntaxErr(int line, int column, int length, TokType expected,
		TokType actual, std::string str);
	virtual ~SyntaxErr(void) { }

	char const * what(void) const throw();
	int line() const;
	int column() const;
	int length() const;

private:
	std::string message_;
	int const line_;
	int const column_;
	int const length_;
};

class Parser {
public:
	Parser(char const * file);
	virtual ~Parser() { };
	// Parser(Parser const & other) =delete;
	// Parser & operator=(Parser const & rhs) =delete;

	std::queue<Instruction> source();

	void printError(TokErr const & e);

private:
	SyntaxErr error(Token token, TokType type);
	bool verify(TokType type); // get next token if types match
	void assert(TokType type); // same but raise an exception in case they don't
	Instruction instr();
	std::array<std::string, 2> value();

	std::string file_;
	std::stringstream source_;
	Token token_;
};

#endif // PARSER_H_
