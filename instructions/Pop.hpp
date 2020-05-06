#ifndef INSTRUCTIONS_POP_H_
#define INSTRUCTIONS_POP_H_

#include "Instruction.hpp"

class Pop: public Instruction {
public:
	Pop(int count = 1);
	virtual ~Pop(void) { }

	void execute(AbstractStack<IOperand const *> &) const;

private:
	int const count;
};

#endif // INSTRUCTIONS_POP_H_
