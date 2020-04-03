#include "Token.hpp"

Token::Token(enum Token::Type type, int index, int length):
	type_(type), index_(index), length_(length) { }

// Token::Token(Token const & copy):
// 	type_(copy.type_), index_(copy.index_), length_(copy.length_) { }

// Token & Token::operator=(Token const & copy) {
// 	type_ = copy.type_;
// 	index_ = copy.index_;
// 	length_ = copy.length_;
// 	return *this;
// }

enum Token::Type Token::type(void) {
	return type_;
}

//tmp
std::ostream & operator<<(std::ostream & os, Token const & t) {
	std::string type;

	if (t.type_ == Token::Type::instr_0)
		type = "instr0";
	else if (t.type_ == Token::Type::instr_1)
		type = "instr1";
	else if (t.type_ == Token::Type::integer_t)
		type = "int_type";
	else if (t.type_ == Token::Type::decimal_t)
		type = "dec_type";
	else if (t.type_ == Token::Type::integer)
		type = "int_value";
	else if (t.type_ == Token::Type::decimal)
		type = "dec_value";
	else if (t.type_ == Token::Type::lparen)
		type = "lparen";
	else if (t.type_ == Token::Type::rparen)
		type = "rparen";
	else if (t.type_ == Token::Type::sep)
		type = "sep";
	else if (t.type_ == Token::Type::comment)
		type = "comment";
	else if (t.type_ == Token::Type::end)
		type = "end";
	os << "Token (" << type << ")";
	return os;
}

// Exceptions

Token::bad_token::bad_token(int index, int length):
	index_(index), length_(length) { }

// Token::bad_token::bad_token(Token::bad_token const & copy):
// 	index_(copy.index_), length_(copy.length_) { }

const char * Token::bad_token::what() const throw() {
	return "Invalid token";
}

int Token::bad_token::index() {
	return index_;
}

int Token::bad_token::length() {
	return length_;
}
