#include "OperandExceptions.hpp"

OperandOverflow::OperandOverflow(): std::overflow_error("overflow error.") { }

char const * OperandOverflow::what() const throw() {
	return std::overflow_error::what();
}

OperandUnderflow::OperandUnderflow(): std::underflow_error("underflow error.") { }

char const * OperandUnderflow::what() const throw() {
	return std::underflow_error::what();
}

OperandDomainError::OperandDomainError(): std::domain_error("domain error.") { }

char const * OperandDomainError::what() const throw() {
	return std::domain_error::what();
}
