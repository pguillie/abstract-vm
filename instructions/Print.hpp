#ifndef INSTRUCTIONS_PRINT_H
#define INSTRUCTIONS_PRINT_H

#include "Instruction.hpp"

class Print: public Instruction {
public:
	Print(int count = 1);
	virtual ~Print() { }

	void execute(AbstractStack<IOperand const *> &) const;

private:
	int const count;
};

#endif // INSTRUCTIONS_PRINT_H
