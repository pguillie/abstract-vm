#ifndef TOKEN_ERROR_H_
#define TOKEN_ERROR_H_

#include "Token.hpp"

class TokenError: public std::exception {
public:
	TokenError(Token err);//, char const * const descr);
	virtual ~TokenError() { }
	// bad_token(bad_token const & copy);
	// bad_token & operator=(bad_token const & copy) =delete;
	// bad_token(bad_token && move) =delete;
	// bad_token & operator=(bad_token && move) =delete;

	virtual char const * what() const throw();

	Token err_;
	// char const * const descr_;
};

#endif // TOKEN_ERROR_H_
