#ifndef INSTRUCTIONS_DUMP_H
#define INSTRUCTIONS_DUMP_H

#include "Instruction.hpp"

class Dump: public Instruction {
public:
	Dump(int count = 0);
	virtual ~Dump() { }

	void execute(AbstractStack<const IOperand*>&) const;

private:
	const int count;
};

#endif // INSTRUCTIONS_DUMP_H
