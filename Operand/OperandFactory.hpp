#ifndef OPERAND_OPERANDFACTORY_H_
#define OPERAND_OPERANDFACTORY_H_

#include <string>

#include "IOperand.hpp"

class OperandFactory;
typedef const IOperand* (OperandFactory::*fptrCreate)(const std::string& value)
	const;

class OperandFactory {
public:
	const IOperand* createOperand(eOperandType type, const std::string& value)
		const;

private:
	const IOperand* createInt8(const std::string& value) const;
	const IOperand* createInt16(const std::string& value) const;
	const IOperand* createInt32(const std::string& value) const;
	const IOperand* createFloat(const std::string& value) const;
	const IOperand* createDouble(const std::string& value) const;

	static const fptrCreate createType[5];
};

#endif // OPERAND_OPERANDFACTORY_H_
