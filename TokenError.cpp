#include <sstream>

#include "TokenError.hpp"

TokenError::TokenError(Token err):
	err_(err) { }

const char * TokenError::what() const throw() {
	std::stringstream msg;

	msg << "Invalid token (" << err_.index_ << ", " << err_.length_ << ")";
	return msg.str().c_str();
}
