#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <sstream>
#include <set>

#include "Token.hpp"

namespace Lexer {
	Token const get(std::istream & source);

	std::set<std::string> const instructions = {
		"push", "pop", "dump", "assert", "add", "sub", "mul",
		"div", "mod", "print", "exit", "and", "or", "xor"
	};
	std::set<std::string> const types = {
		"int8", "int16", "int32", "float", "double"
	};
}

class LexicalErr: public virtual TokErr {
public:
	LexicalErr(int line, int column, int length, std::string lexeme);
	virtual ~LexicalErr(void) { }

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

#endif // LEXER_H_
