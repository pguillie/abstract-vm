#ifndef INSTRUCTIONS_PRINT_H
#define INSTRUCTIONS_PRINT_H

#include "Instruction.hpp"

class Print: public Instruction {
public:
	Print(int count = 1);
	virtual ~Print() { }

	void execute(AbstractStack<IOperand const *> &) const;

	class TypeException: public Instruction::StdExcept {
	public:
//		TypeException();
		virtual ~TypeException() { }
		char const * what() const throw();
	};

private:
	int const count;
};

#endif // INSTRUCTIONS_PRINT_H
