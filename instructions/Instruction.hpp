#ifndef INSTRUCTIONS_INSTRUCTION_H_
#define INSTRUCTIONS_INSTRUCTION_H_

#include <iostream>

#include "../IOperand.hpp"
#include "../AbstractStack.hpp"

using std::cout;

class Instruction {
public:
	virtual ~Instruction(void) { }

	virtual void execute(AbstractStack<const IOperand*>& stack) const =0;

	void setVerbose(bool on = true);

	// Top-level base class for instructions exceptions.
	// Actual instructions exceptions should however derive from StdExcept,
	// to also inherit from std::exception (see below).
	class Exception {
	public:
		virtual ~Exception() { }
		virtual const char* what() const throw() =0;
	};

	class StackOutOfRange: public Exception, public std::out_of_range {
	public:
		StackOutOfRange(const char* what_arg);
		virtual ~StackOutOfRange() { }

		const char* what() const throw();
	};

protected:
	bool verbose = false;

	class StdExcept: public Exception, public std::exception {
	public:
		virtual ~StdExcept() { }

		virtual const char* what() const throw() =0;
	};
};

#endif // INSTRUCTIONS_INSTRUCTION_H_
