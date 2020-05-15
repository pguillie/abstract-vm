#ifndef OPERAND_EXCEPTIONS_H_
#define OPERAND_EXCEPTIONS_H_

#include <stdexcept>

class OperandException {
public:
	virtual ~OperandException() { }

	virtual const char* what() const throw() =0;
};

class OperandOverflow: public OperandException, public std::overflow_error {
public:
	OperandOverflow();
	virtual ~OperandOverflow() { }

	const char* what() const throw();
};

class OperandUnderflow: public OperandException, public std::underflow_error {
public:
	OperandUnderflow();
	virtual ~OperandUnderflow() { }

	const char* what()  const throw();
};

class OperandDomainError: public OperandException, public std::domain_error {
public:
	OperandDomainError(const std::string& what_arg);
	virtual ~OperandDomainError() { }

	const char* what() const throw();
};

#endif // OPERAND_EXCEPTIONS_H_
