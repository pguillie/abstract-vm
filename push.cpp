#include "avm.hpp"
#include "OperandFactory.hpp"

void avm::push(AbstractStack<IOperand const *> & stack,
	std::vector<std::array<std::string, 2>> args) {
	IOperand const * operand;
	std::map<std::string, eOperandType> const type = {
		{"int8", INT8},
		{"int16", INT16},
		{"int32", INT32},
		{"float", FLOAT},
		{"double", DOUBLE}
	};

	for (auto const & arg : args) {
		operand = factory.createOperand(type.at(arg.front()), arg.back());
		stack.push(operand);
	}
}
