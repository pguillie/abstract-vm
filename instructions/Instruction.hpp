#ifndef INSTRUCTIONS_INSTRUCTION_H_
#define INSTRUCTIONS_INSTRUCTION_H_

#include <iostream>

#include "../IOperand.hpp"
#include "../AbstractStack.hpp"

using std::cout;

class Instruction {
public:
	virtual ~Instruction(void) { }

	virtual void execute(AbstractStack<IOperand const*>& stack) const =0;

	void setVerbose(bool on = true);

protected:
	bool verbose = false;
};

#endif // INSTRUCTIONS_INSTRUCTION_H_
