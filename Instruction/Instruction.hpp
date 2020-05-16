#ifndef INSTRUCTION_INSTRUCTION_H_
#define INSTRUCTION_INSTRUCTION_H_

#include <iostream>

#include "Operand/IOperand.hpp"
#include "AbstractStack.hpp"

using std::cout;

class Instruction {
public:
	Instruction(void);
	Instruction(const Instruction& o) =delete;
	Instruction(Instruction&& o) =delete;
	virtual ~Instruction(void);
	Instruction& operator=(const Instruction& o) =delete;
	Instruction& operator=(Instruction&& o) =delete;

	virtual void execute(AbstractStack<const IOperand*>& stack) const =0;
	void setVerbose(bool on = true);

	// Top-level base class for instructions exceptions.
	// Actual instructions exceptions should however derive from StdExcept,
	// to also inherit from std::exception (see below).
	class Exception {
	public:
		virtual ~Exception(void) { }

		virtual const char* what(void) const throw() =0;
	};

	class StackOutOfRange: public Exception, public std::out_of_range {
	public:
		StackOutOfRange(void);
		StackOutOfRange(const StackOutOfRange& o) =delete;
		StackOutOfRange(StackOutOfRange&& o) =delete;
		StackOutOfRange(const char* what_arg);
		virtual ~StackOutOfRange(void);
		StackOutOfRange& operator=(const StackOutOfRange& o) =delete;
		StackOutOfRange& operator=(StackOutOfRange&& o) =delete;

		const char* what(void) const throw();
	};

protected:
	bool verbose;

	class StdExcept: public Exception, public std::exception {
	public:
		virtual ~StdExcept(void) { }

		virtual const char* what(void) const throw() =0;
	};
};

#endif // INSTRUCTION_INSTRUCTION_H_
