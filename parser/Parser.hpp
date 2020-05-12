#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <stdexcept>

#include "Token.hpp"
#include "Lexer.hpp"
#include "../Value.hpp"
#include "../instructions/Push.hpp"
#include "../instructions/Pop.hpp"
#include "../instructions/Dump.hpp"
#include "../instructions/Assert.hpp"
#include "../instructions/Operation.hpp"
#include "../instructions/Print.hpp"
#include "../instructions/Exit.hpp"

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

class Parser;
typedef Instruction * (Parser::*fptr)(void);

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
	Instruction * avm_push();
	Instruction * avm_pop();
	Instruction * avm_dump();
	Instruction * avm_assert();
	Instruction * avm_add();
	Instruction * avm_sub();
	Instruction * avm_mul();
	Instruction * avm_div();
	Instruction * avm_mod();
	Instruction * avm_operation(Operation::Type op);
	Instruction * avm_print();
	Instruction * avm_exit();

	Value value(Token t);

	SyntaxErr error(Token token, TokType type);
	Token assert(Token token, TokType type);

	std::stringstream source_;
	Token token_;

	static std::map<std::string, fptr> instructions;
};

#endif // PARSER_H_
