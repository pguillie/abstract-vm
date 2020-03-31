#include "Token.hpp"

Token::Token(enum Token::Type type, int index, int length):
	type(type), index(index), length(length) {
}

Token::Token(Token const & other):
	type(other.type), index(other.index), length(other.length) {
}

Token & Token::operator=(Token const & t) {
	type = t.type;
	index = t.index;
	length = t.length;
	return *this;
}

enum Token::Type Token::getType(void) {
	return type;
}

std::ostream & operator<<(std::ostream & os, Token const & t) {
	std::string type;

	if (t.type == Token::Type::instr0)
		type = "instr0";
	else if (t.type == Token::Type::instr1)
		type = "instr1";
	else if (t.type == Token::Type::int_type)
		type = "int_type";
	else if (t.type == Token::Type::dec_type)
		type = "dec_type";
	else if (t.type == Token::Type::int_value)
		type = "int_value";
	else if (t.type == Token::Type::dec_value)
		type = "dec_value";
	else if (t.type == Token::Type::lparen)
		type = "lparen";
	else if (t.type == Token::Type::rparen)
		type = "rparen";
	else if (t.type == Token::Type::sep)
		type = "sep";
	else if (t.type == Token::Type::comment)
		type = "comment";
	else if (t.type == Token::Type::end)
		type = "end";
	os << "Token (" << type << ")";
	return os;
}

// Exceptions

Token::bad_token::bad_token(int index, int length):
	index(index), length(length) {
}

Token::bad_token::bad_token(Token::bad_token const & other):
	index(other.index), length(other.length) {
}

const char * Token::bad_token::what() const throw() {
	return "Invalid token";
}
