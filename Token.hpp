#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <limits>

class Token {
public:
	enum class Type {
		instr0, instr1, int_type, dec_type, int_value, dec_value,
		lparen, rparen, sep, comment, end
	};

	Token(void);
	Token(enum Type type);
	Token(enum Type type, int index, int length);
	virtual ~Token() {};
	Token & operator=(Token const & t);

	enum Type getType(void);

	friend std::ostream & operator<<(std::ostream & os, Token const & token);

private:
	enum Type type;
	int index;
	int length;
};

#endif // TOKEN_H_
