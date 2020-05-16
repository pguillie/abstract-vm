#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

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
#include "Instruction/Value.hpp"
#include "Instruction/Push.hpp"
#include "Instruction/Pop.hpp"
#include "Instruction/Dump.hpp"
#include "Instruction/Assert.hpp"
#include "Instruction/Operation.hpp"
#include "Instruction/Print.hpp"
#include "Instruction/Exit.hpp"

class SyntaxErr: public virtual TokErr {
public:
	SyntaxErr(void) =delete;
	SyntaxErr(const SyntaxErr& o) =delete;
	SyntaxErr(SyntaxErr&& o) =delete;
	SyntaxErr(int line, int column, int length, TokType expected,
		TokType actual, std::string str);
	virtual ~SyntaxErr(void);
	SyntaxErr& operator=(const SyntaxErr& o) =delete;
	SyntaxErr& operator=(SyntaxErr&& o) =delete;

	const char* what(void) const throw();
	int line(void) const;
	int column(void) const;
	int length(void) const;

private:
	std::string message_;
	const int line_;
	const int column_;
	const int length_;
};

class Parser;
typedef Instruction * (Parser::*fptr)(void);

class Parser {
public:
	Parser(void);
	Parser(const Parser& o) =delete;
	Parser(Parser&& o) =delete;
	virtual ~Parser(void);
	Parser& operator=(const Parser& o) =delete;
	Parser& operator=(Parser&& o) =delete;

	std::queue<Instruction*> source(void);
	Instruction* instruction(void);

	void setSource(std::stringstream& source);
	void printError(std::string file, const TokErr& e);

private:
	Instruction* avm_push(void);
	Instruction* avm_pop(void);
	Instruction* avm_dump(void);
	Instruction* avm_assert(void);
	Instruction* avm_add(void);
	Instruction* avm_sub(void);
	Instruction* avm_mul(void);
	Instruction* avm_div(void);
	Instruction* avm_mod(void);
	Instruction* avm_and(void);
	Instruction* avm_or(void);
	Instruction* avm_xor(void);
	Instruction* avm_operation(Operation::Type op);
	Instruction* avm_print(void);
	Instruction* avm_exit(void);

	std::vector<Value> value_args(unsigned int min);
	Value value(Token t);
	int int_arg(void);

	SyntaxErr error(Token token, TokType type);
	Token assert(Token token, TokType type);

	std::stringstream source_;

	static std::map<std::string, fptr> instructions;
};

#endif // PARSER_PARSER_H_
