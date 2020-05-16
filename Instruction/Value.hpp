#ifndef INSTRUCTION_VALUE_H_
#define INSTRUCTION_VALUE_H_

#include "Operand/Operand.hpp"

struct Value {
	eOperandType type;
	std::string value;
};

#endif // INSTRUCTION_VALUE_H_
