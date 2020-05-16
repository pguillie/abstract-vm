#include <limits>

#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "OperandExceptions.hpp"

const fptrCreate OperandFactory::createType[5] = {
	[INT8] = &OperandFactory::createInt8,
	[INT16] = &OperandFactory::createInt16,
	[INT32] = &OperandFactory::createInt32,
	[FLOAT] = &OperandFactory::createFloat,
	[DOUBLE] = &OperandFactory::createDouble
};

const IOperand* OperandFactory::createOperand(eOperandType type,
	const std::string& value) const
{
	return (this->*createType[type])(value);
}

template <class N>
const IOperand* create(const std::string& value)
{
	double n(std::stod(value));

	if (n > std::numeric_limits<N>::max())
		throw OperandOverflow();
	if (n < std::numeric_limits<N>::lowest())
		throw OperandUnderflow();
	return new Operand<N>((N)std::stod(value));
}

const IOperand* OperandFactory::createInt8(const std::string& value) const
{
	return create<int8_t>(value);
}

const IOperand* OperandFactory::createInt16(const std::string& value) const
{
	return create<int16_t>(value);
}

const IOperand* OperandFactory::createInt32(const std::string& value) const
{
	return create<int32_t>(value);
}

const IOperand* OperandFactory::createFloat(const std::string& value) const
{
	return create<float>(value);
}

const IOperand* OperandFactory::createDouble(const std::string& value) const
{
	return create<double>(value);
}
