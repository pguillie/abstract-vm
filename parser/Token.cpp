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
	case TokType::instruction:
		return "instruction";
	case TokType::type:
		return "numeric type";
	case TokType::integer:
		return "integer value";
	case TokType::decimal:
		return "decimal value";
	case TokType::lparen:
		return "‘(’";
	case TokType::rparen:
		return "‘)’";
	case TokType::comma:
		return "‘,’";
	case TokType::newline:
		return "newline";
	case TokType::eof:
		return "end-of-file";
	default:
		return "unknown";
	}
}
