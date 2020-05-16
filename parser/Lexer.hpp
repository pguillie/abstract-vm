#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <sstream>
#include <set>

#include "Token.hpp"

namespace Lexer {
	const Token get(std::istream& source);

	const std::set<std::string> instructions = {
		"push", "pop", "dump", "assert", "add", "sub", "mul",
		"div", "mod", "print", "exit", "and", "or", "xor"
	};
	const std::set<std::string> types = {
		"int8", "int16", "int32", "float", "double"
	};
}

class LexicalErr: public virtual TokErr {
public:
	LexicalErr(void) =delete;
	LexicalErr(const LexicalErr& o) =delete;
	LexicalErr(LexicalErr&& o) =delete;
	LexicalErr(int line, int column, int length, std::string lexeme);
	virtual ~LexicalErr(void);
	LexicalErr& operator=(const LexicalErr& o) =delete;
	LexicalErr& operator=(LexicalErr&& o) =delete;

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

#endif // LEXER_H_
