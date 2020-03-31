#include "Lexer.hpp"

Lexer::Lexer(): input(std::cin) {
}

Lexer::Lexer(std::istream & input): input(input) {
}

Token const Lexer::getNextToken() {
	char c;

	while (std::isblank(input.peek()))
		input.ignore();
	c = input.peek();
	switch (c) {
	case EOF:
		return Token(Token::Type::end);
	case '(':
		input.ignore();
		return Token(Token::Type::lparen);
	case ')':
		input.ignore();
		return Token(Token::Type::rparen);
	case '\n':
		input.ignore();
		return Token(Token::Type::sep);
	case ';':
		return comment();
	}
	if (std::isalpha(c))
		return keyword();
	if (std::isdigit(c) || c == '-' || c == '.')
		return value();
	throw Token::bad_token(input.tellg());
}

Token const Lexer::keyword() {
	std::map<std::string, Token::Type>::const_iterator i;
	std::string word;
	int index = input.tellg();

	while (std::isalnum(input.peek()))
		word += input.get();
	i = keywords.find(word);
	if (i == keywords.end())
		throw Token::bad_token(index, word.length());
	return Token(i->second, index, word.length());
}

Token const Lexer::value() {
	int index = input.tellg();
	int digit = 0;
	Token::Type t;
	char c;

	if (input.peek() == '-')
		input.ignore();
	while (input.get(c) && std::isdigit(c))
		digit++;
	if (c != '.') {
		t = Token::Type::int_value;
	} else {
		t = Token::Type::dec_value;
		while (std::isdigit(input.get()))
			digit++;
	}
	input.unget();
	if (!digit)
		throw Token::bad_token(index, (int)input.tellg() - index);
	return Token(t, index, (int)input.tellg() - index);
}

Token const Lexer::comment() {
	int index = input.tellg();

	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return Token(Token::Type::comment, index, (int)input.tellg() - index);
}

// Static member variables

std::map<std::string, Token::Type> const Lexer::keywords = {
	{"push", Token::Type::instr1},
	{"pop", Token::Type::instr0},
	{"dump", Token::Type::instr0},
	{"assert", Token::Type::instr1},
	{"add", Token::Type::instr0},
	{"sub", Token::Type::instr0},
	{"mul", Token::Type::instr0},
	{"div", Token::Type::instr0},
	{"mod", Token::Type::instr0},
	{"print", Token::Type::instr0},
	{"exit", Token::Type::instr0},
	{"int8", Token::Type::int_type},
	{"int16", Token::Type::int_type},
	{"int32", Token::Type::int_type},
	{"float", Token::Type::dec_type},
	{"double", Token::Type::dec_type}
};
