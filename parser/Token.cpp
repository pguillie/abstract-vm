#include "Token.hpp"

Token::Token(void):
	type_(TokType::eof), index_(0), length_(0)
{ }

Token::Token(const Token& o):
	type_(o.type_), index_(o.index_), length_(o.length_)
{ }

Token::Token(Token&& o):
	type_(o.type_), index_(o.index_), length_(o.length_)
{
	o.type_ = TokType::eof;
	o.index_ = 0;
	o.length_ = 0;
}

Token::Token(enum TokType type, int index):
	Token::Token(type, index, 1)
{ }

Token::Token(enum TokType type, int index, int length):
	type_(type), index_(index), length_(length)
{ }

Token::~Token(void)
{ }

Token& Token::operator=(const Token& o)
{
	if (this != &o) {
		type_ = o.type_;
		index_ = o.index_;
		length_ = o.length_;
	}
	return *this;
}

Token& Token::operator=(Token&& o)
{
	if (this != &o) {
		type_ = o.type_;
		index_ = o.index_;
		length_ = o.length_;
		o.type_ = TokType::eof;
		o.index_ = 0;
		o.length_ = 0;
	}
	return *this;
}

enum TokType Token::type(void) const
{
	return type_;
}

int Token::index(void) const
{
	return index_;
}

int Token::length(void) const
{
	return length_;
}

std::string Token::toString(TokType type)
{
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
		return "(unknown type)";
	}
}
