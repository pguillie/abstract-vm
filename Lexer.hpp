#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "Token.hpp"

class Lexer {
public:
	// Lexer(char const * file = NULL);
	// virtual ~Lexer() { };
	Lexer(std::istream & input);

	// Lexer(Lexer const & copy) =delete;
	// Lexer & operator=(Lexer const & copy) =delete;
	// Lexer(Lexer && move) =delete;
	// Lexer & operator=(Lexer && move) =delete;

	Token const get();

private:
	// std::stringstream ss_;
	// std::ifstream fs_;
	// std::istream * input_;
	std::istream & source_;
	static std::map<std::string, Token::Type> const keywords_;

	Token const word();
	Token const number();
	Token const comment();
};

#endif // LEXER_H_
