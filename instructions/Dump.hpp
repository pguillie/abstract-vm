#ifndef INSTRUCTIONS_DUMP_H
#define INSTRUCTIONS_DUMP_H

#include "Instruction.hpp"

class Dump: public Instruction {
public:
	Dump(void);
	Dump(const Dump& o) =delete;
	Dump(Dump&& o) =delete;
	Dump(int count);
	virtual ~Dump(void);
	Dump& operator=(const Dump& o) =delete;
	Dump& operator=(Dump&& o) =delete;

	void execute(AbstractStack<const IOperand*>& stack) const;

private:
	const int count;
};

#endif // INSTRUCTIONS_DUMP_H
