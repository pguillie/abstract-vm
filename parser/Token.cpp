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

std::string Token::toString(TokType type) {
	switch (type) {
	case TokType::instr_0:
		return "instruction";
	case TokType::instr_1:
		return "instruction";
	case TokType::integer_t:
		return "numeric type";
	case TokType::decimal_t:
		return "numeric type";
	case TokType::integer:
		return "integer value";
	case TokType::decimal:
		return "decimal value";
	case TokType::lparen:
		return "parenthese";
	case TokType::rparen:
		return "parenthese";
	case TokType::newline:
		return "newline";
	case TokType::end:
		return "end-of-file";
	default:
		return "unknown";
	}
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
	else
		type = "unknown";
	os << "Token: " << type << "(" << t.index_ << ", " << t.length_ << ")";
	return os;
}
