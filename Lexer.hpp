#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <map>

#include "Token.hpp"
#include "TokenError.hpp"

namespace Lexer {
	Token const get(std::istream & source);
	//static std::map<std::string, Token::Type> const keywords;
	std::map<std::string, Token::Type> const keywords = {
	{"push", Token::Type::instr_1},
	{"pop", Token::Type::instr_0},
	{"dump", Token::Type::instr_0},
	{"assert", Token::Type::instr_1},
	{"add", Token::Type::instr_0},
	{"sub", Token::Type::instr_0},
	{"mul", Token::Type::instr_0},
	{"div", Token::Type::instr_0},
	{"mod", Token::Type::instr_0},
	{"print", Token::Type::instr_0},
	{"exit", Token::Type::instr_0},
	{"int8", Token::Type::integer_t},
	{"int16", Token::Type::integer_t},
	{"int32", Token::Type::integer_t},
	{"float", Token::Type::decimal_t},
	{"double", Token::Type::decimal_t}
};

}

#endif // LEXER_H_
