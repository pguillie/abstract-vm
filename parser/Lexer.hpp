#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <sstream>
#include <map>

#include "Token.hpp"

namespace Lexer {
	Token const get(std::istream & source);

	std::map<std::string, TokType> const keywords = {
		{"push", TokType::instr_1},
		{"pop", TokType::instr_0},
		{"dump", TokType::instr_0},
		{"assert", TokType::instr_1},
		{"add", TokType::instr_0},
		{"sub", TokType::instr_0},
		{"mul", TokType::instr_0},
		{"div", TokType::instr_0},
		{"mod", TokType::instr_0},
		{"print", TokType::instr_0},
		{"exit", TokType::instr_0},
		{"int8", TokType::integer_t},
		{"int16", TokType::integer_t},
		{"int32", TokType::integer_t},
		{"float", TokType::decimal_t},
		{"double", TokType::decimal_t}
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
