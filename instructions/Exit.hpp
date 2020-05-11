#ifndef INSTRUCTIONS_EXIT_H_
#define INSTRUCTIONS_EXIT_H_

#include "Instruction.hpp"

class Exit: public Instruction {
public:
	Exit();
	virtual ~Exit() { }

	void execute(AbstractStack<IOperand const *> &) const;

	class Exception: public std::exception {
	public:
		virtual ~Exception() { }
		char const * what() const throw();
	};
};

#endif // INSTRUCTIONS_EXIT_H_
