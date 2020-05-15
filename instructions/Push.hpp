#ifndef INSTRUCTIONS_PUSH_H_
#define INSTRUCTIONS_PUSH_H_

#include <vector>

#include "Instruction.hpp"
#include "../OperandFactory.hpp"
#include "../Value.hpp"

class Push: public Instruction {
public:
	Push(const std::vector<Value>&);
	virtual ~Push(void) { }

	void execute(AbstractStack<const IOperand*>&) const;

private:
	const std::vector<Value> args;
	static const OperandFactory factory;
};

#endif // INSTRUCTIONS_PUSH_H_
