#ifndef INSTRUCTION_OPERATION_H_
#define INSTRUCTION_OPERATION_H_

#include <vector>

#include "Instruction.hpp"
#include "Value.hpp"
#include "Operand/OperandFactory.hpp"

class Operation: public Instruction {
public:
	enum class Type {
		add, sub, mul, div, mod, bw_and, bw_or, bw_xor
	};

	Operation(void) =delete;
	Operation(const Operation& o) =delete;
	Operation(Operation&& o) =delete;
	Operation(enum Type op, const std::vector<Value>&);
	virtual ~Operation(void);
	Operation& operator=(const Operation& o) =delete;
	Operation& operator=(Operation&& o) =delete;

	void execute(AbstractStack<const IOperand*>& stack) const;

private:
	void calc(AbstractStack<const IOperand*>& stack, const IOperand* rhs)
		const;

	const enum Type op;
	const std::vector<Value> args;
	static const OperandFactory factory;
};

#endif // INSTRUCTION_OPERATION_H_
