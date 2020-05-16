#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <limits>
#include <exception>
#include <string>

// All possible types a Token can have.
enum class TokType {
	instruction, type, integer, decimal, lparen, rparen, comma, newline, eof
};

// Interface to handle lexical errors.
class TokErr: public virtual std::exception {
public:
	virtual ~TokErr(void) { }

	virtual const char* what(void) const throw() =0;
	virtual int line(void) const =0;
	virtual int column(void) const =0;
	virtual int length(void) const =0;
};

// A Token is the association of a portion of the source code with a type.
class Token {
public:
	Token(void);
	Token(const Token& o);
	Token(Token&& o);
	Token(enum TokType type, int index);
	Token(enum TokType type, int index, int length);
	virtual ~Token(void);
	Token& operator=(const Token& o);
	Token& operator=(Token&& o);

	enum TokType type(void) const;
	int index(void) const;
	int length(void) const;

	static std::string toString(TokType type);

private:
	void error(void) const;

	enum TokType type_;
	int index_;
	int length_;
};

#endif // TOKEN_H_
