#ifndef INSTRUCTIONS_OPERATION_H_
#define INSTRUCTIONS_OPERATION_H_

#include <vector>

#include "Instruction.hpp"
#include "../OperandFactory.hpp"
#include "../Value.hpp"

class Operation: public Instruction {
public:
	enum class Type { add, sub, mul, div, mod };

	Operation(enum Type op, std::vector<Value> const &);
	virtual ~Operation() { }

	void execute(AbstractStack<IOperand const *> &) const;

private:
	void calc(AbstractStack<IOperand const *> &, IOperand const *) const;

	enum Type const op;
	std::vector<Value> const args;
	static OperandFactory const factory;
};

#endif // INSTRUCTIONS_OPERATION_H_
