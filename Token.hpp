#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <limits>
#include <exception>

class Token {
public:
	enum class Type {
		instr0, instr1, int_type, dec_type, int_value, dec_value,
		lparen, rparen, sep, comment, end
	};

	Token(enum Type type = Type::end, int index = -1, int length = -1);
	Token(Token const & other);
	virtual ~Token() {};
	Token & operator=(Token const & t);

	enum Type getType(void);

	friend std::ostream & operator<<(std::ostream & os, Token const & token);

	class bad_token: public std::exception {
	public:
		bad_token(int index, int length = 1);
		bad_token(bad_token const & other);
		virtual ~bad_token() {}

		virtual char const * what() const throw();

	private:
		bad_token();
		bad_token & operator=(bad_token const & rhs);

		int index;
		int length;
	};

private:
	enum Type type;
	int index;
	int length;
};

#endif // TOKEN_H_
