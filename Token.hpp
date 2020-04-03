#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <limits>
#include <exception>

class Token {
public:
	enum class Type {
		instr_0, instr_1, integer_t, decimal_t, integer, decimal,
		lparen, rparen, sep, comment, end
	};

	Token(enum Type type = Type::end, int index = -1, int length = -1);
	virtual ~Token() { };
	// Token(Token const & copy);
	// Token & operator=(Token const & copy);
	// Token(Token && move) =delete;
	// Token & operator=(Token && copy) =delete;

	enum Type type();

	//tmp
	friend std::ostream & operator<<(std::ostream & os, Token const & token);

	class bad_token: public std::exception {
	public:
		bad_token(int index, int length = 1);
		virtual ~bad_token() { }
		// bad_token(bad_token const & copy);
		// bad_token & operator=(bad_token const & copy) =delete;
		// bad_token(bad_token && move) =delete;
		// bad_token & operator=(bad_token && move) =delete;

		virtual char const * what() const throw();

		int index();
		int length();

	private:
		int index_;
		int length_;
	};

private:
	enum Type type_;
	int index_;
	int length_;
};

#endif // TOKEN_H_
