#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <limits>
#include <exception>

class Token {
public:
	enum class Type {
		instr_0, instr_1, integer_t, decimal_t, integer, decimal,
		lparen, rparen, newline, end, none
	};

	Token() =default;
	Token(enum Type type, int index, int length = 1);
	virtual ~Token() { };
	// Token(Token const & copy);
	// Token & operator=(Token const & copy);
	// Token(Token && move) =delete;
	// Token & operator=(Token && copy) =delete;

	enum Type type();
	int index();
	int length();

	//tmp
	friend std::ostream & operator<<(std::ostream & os, Token const & token);

	friend class TokenError;

private:
	enum Type type_;
	int index_;
	int length_;
};

#endif // TOKEN_H_
