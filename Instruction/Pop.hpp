#ifndef INSTRUCTION_POP_H_
#define INSTRUCTION_POP_H_

#include "Instruction.hpp"

class Pop: public Instruction {
public:
	Pop(void);
	Pop(const Pop& o) =delete;
	Pop(Pop&& o) =delete;
	Pop(int count);
	virtual ~Pop(void);
	Pop& operator=(const Pop& o) =delete;
	Pop& operator=(Pop&& o) =delete;

	void execute(AbstractStack<const IOperand*>& stack) const;

private:
	const int count;
};

#endif // INSTRUCTION_POP_H_
