#ifndef INSTRUCTIONS_PUSH_H_
#define INSTRUCTIONS_PUSH_H_

#include <vector>

#include "Instruction.hpp"
#include "../OperandFactory.hpp"
#include "../Value.hpp"

class Push: public Instruction {
public:
	Push(std::vector<Value> const &);
	virtual ~Push(void) { }

	void execute(AbstractStack<IOperand const *> &) const;

private:
	std::vector<Value> const args;
	static OperandFactory const factory;
};

#endif // INSTRUCTIONS_PUSH_H_
