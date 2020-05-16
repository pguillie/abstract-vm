#include "OperandExceptions.hpp"

OperandOverflow::OperandOverflow(void):
	std::overflow_error("overflow error")
{ }

OperandOverflow::~OperandOverflow(void)
{ }

const char* OperandOverflow::what(void) const throw()
{
	return std::overflow_error::what();
}

OperandUnderflow::OperandUnderflow(void):
	std::underflow_error("underflow error")
{ }

OperandUnderflow::~OperandUnderflow(void)
{ }

const char* OperandUnderflow::what(void) const throw()
{
	return std::underflow_error::what();
}

OperandDomainError::OperandDomainError(const std::string& what_arg):
	std::domain_error(what_arg)
{ }

OperandDomainError::~OperandDomainError(void)
{ }

const char* OperandDomainError::what() const throw()
{
	return std::domain_error::what();
}
