#include "Token.hpp"

Token::Token(enum TokType type, int index, int length):
	type_(type), index_(index), length_(length) { }

enum TokType Token::type() const {
	return type_;
}

int Token::index() const {
	return index_;
}

int Token::length() const {
	return length_;
}

//tmp
std::ostream & operator<<(std::ostream & os, Token const & t) {
	std::string type;

	if (t.type_ == TokType::instr_0)
		type = "instr0";
	else if (t.type_ == TokType::instr_1)
		type = "instr1";
	else if (t.type_ == TokType::integer_t)
		type = "int_type";
	else if (t.type_ == TokType::decimal_t)
		type = "dec_type";
	else if (t.type_ == TokType::integer)
		type = "int_value";
	else if (t.type_ == TokType::decimal)
		type = "dec_value";
	else if (t.type_ == TokType::lparen)
		type = "lparen";
	else if (t.type_ == TokType::rparen)
		type = "rparen";
	else if (t.type_ == TokType::newline)
		type = "newline";
	else if (t.type_ == TokType::end)
		type = "end";
	os << "Token: " << type << "(" << t.index_ << ", " << t.length_ << ")";
	return os;
}
