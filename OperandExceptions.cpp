#include "OperandExceptions.hpp"

OperandOverflow::OperandOverflow():
	std::overflow_error("overflow error")
{ }

const char* OperandOverflow::what() const throw()
{
	return std::overflow_error::what();
}

OperandUnderflow::OperandUnderflow():
	std::underflow_error("underflow error")
{ }

const char* OperandUnderflow::what() const throw()
{
	return std::underflow_error::what();
}

OperandDomainError::OperandDomainError(const std::string& what_arg):
	std::domain_error(what_arg)
{ }

const char* OperandDomainError::what() const throw()
{
	return std::domain_error::what();
}
