#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <fstream>
#include <map>
#include <exception>

#include "Token.hpp"

class Lexer {
public:
	Lexer();
	Lexer(std::istream & input);
	virtual ~Lexer() {};

	Token const getNextToken();

private:
	Lexer(Lexer const & other);
	Lexer & operator=(Lexer const & rhs);

	Token const keyword();
	Token const value();
	Token const comment();

	std::istream & input;
	static std::map<std::string, Token::Type> const keywords;
};

#endif // LEXER_H_
