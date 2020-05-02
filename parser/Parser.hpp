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
	std::string name;
	std::vector<std::array<std::string, 2>> args;
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
	// Parser();
	virtual ~Parser() { };
	// Parser(Parser const & other) =delete;
	// Parser & operator=(Parser const & rhs) =delete;

	std::queue<Instruction *> source();
	Instruction * instruction();

	void setSource(std::stringstream source);
	void printError(std::string file, TokErr const & e);

private:
	std::array<std::string, 2> value();

	SyntaxErr error(Token token, TokType type);
	Token assert(TokType type);

	std::stringstream source_;
	Token token_;
};

#endif // PARSER_H_
