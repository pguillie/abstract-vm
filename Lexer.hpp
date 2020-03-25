#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <fstream>
#include <map>

#include "Token.hpp"

class Lexer {
public:
	Lexer(std::istream & input);
	virtual ~Lexer(void) {};

	Token const getNextToken(void);

private:
	Token const keyword(void);
	Token const value(void);
	Token const comment(void);

	std::istream & input;
	static std::map<std::string, Token::Type> const keywords;
};

#endif // LEXER_H_
