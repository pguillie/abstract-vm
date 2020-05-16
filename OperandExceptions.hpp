#ifndef OPERAND_EXCEPTIONS_H_
#define OPERAND_EXCEPTIONS_H_

#include <stdexcept>

class OperandException {
public:
	virtual ~OperandException(void) { }

	virtual const char* what(void) const throw() =0;
};

class OperandOverflow: public OperandException, public std::overflow_error {
public:
	OperandOverflow(void);
	OperandOverflow(const OperandOverflow& o) =delete;
	OperandOverflow(OperandOverflow&& o) =delete;
	virtual ~OperandOverflow(void);
	OperandOverflow& operator=(const OperandOverflow& o) =delete;
	OperandOverflow& operator=(OperandOverflow&& o) =delete;

	const char* what(void) const throw();
};

class OperandUnderflow: public OperandException, public std::underflow_error {
public:
	OperandUnderflow(void);
	OperandUnderflow(const OperandUnderflow& o) =delete;
	OperandUnderflow(OperandUnderflow&& o) =delete;
	virtual ~OperandUnderflow(void);
	OperandUnderflow& operator=(const OperandUnderflow& o) =delete;
	OperandUnderflow& operator=(OperandUnderflow&& o) =delete;

	const char* what(void)  const throw();
};

class OperandDomainError: public OperandException, public std::domain_error {
public:
	OperandDomainError(void) =delete;
	OperandDomainError(const OperandDomainError& o) =delete;
	OperandDomainError(OperandDomainError&& o) =delete;
	OperandDomainError(const std::string& what_arg);
	virtual ~OperandDomainError(void);
	OperandDomainError& operator=(const OperandDomainError& o) =delete;
	OperandDomainError& operator=(OperandDomainError&& o) =delete;

	const char* what(void) const throw();
};

#endif // OPERAND_EXCEPTIONS_H_
