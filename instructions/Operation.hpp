#ifndef INSTRUCTIONS_OPERATION_H_
#define INSTRUCTIONS_OPERATION_H_

#include <vector>

#include "Instruction.hpp"
#include "../OperandFactory.hpp"
#include "../Operand.hpp"
#include "../Value.hpp"

class Operation: public Instruction {
public:
	enum class Type { add, sub, mul, div, mod, bw_and, bw_or, bw_xor };

	Operation(enum Type op, const std::vector<Value>&);
	virtual ~Operation() { }

	void execute(AbstractStack<const IOperand*>&) const;

private:
	void calc(AbstractStack<const IOperand*>&, const IOperand*) const;

	const enum Type op;
	const std::vector<Value> args;
	static const OperandFactory factory;
};

#endif // INSTRUCTIONS_OPERATION_H_
