#include <limits>

#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "OperandExceptions.hpp"

createFunc const OperandFactory::create[5] = {
	[INT8] = &OperandFactory::createInt8,
	[INT16] = &OperandFactory::createInt16,
	[INT32] = &OperandFactory::createInt32,
	[FLOAT] = &OperandFactory::createFloat,
	[DOUBLE] = &OperandFactory::createDouble
};

IOperand const * OperandFactory::createOperand(eOperandType type,
	std::string const & value) const {
	return (this->*create[type])(value);
}

IOperand const * OperandFactory::createInt8(std::string const & value) const {
	double n(std::stod(value));
	if (n > std::numeric_limits<char>::max())
		throw OperandOverflow();
	if (n < std::numeric_limits<char>::min())
		throw OperandUnderflow();
	return new Operand<int8_t>((int8_t)std::stoi(value));
}

IOperand const * OperandFactory::createInt16(std::string const &value) const {
	double n(std::stod(value));
	if (n > std::numeric_limits<char16_t>::max())
		throw OperandOverflow();
	if (n < std::numeric_limits<char16_t>::min())
		throw OperandUnderflow();
	return new Operand<int16_t>((int16_t)std::stoi(value));
}

IOperand const * OperandFactory::createInt32(std::string const &value) const {
	double n(std::stod(value));
	if (n > std::numeric_limits<char32_t>::max())
		throw OperandOverflow();
	if (n < std::numeric_limits<char32_t>::min())
		throw OperandUnderflow();
	return new Operand<int32_t>((int32_t)std::stoi(value));
}

IOperand const * OperandFactory::createFloat(std::string const &value) const {
	double n(std::stod(value));
	if (n > std::numeric_limits<float>::max())
		throw OperandOverflow();
	if (n < std::numeric_limits<float>::min())
		throw OperandUnderflow();
	return new Operand<float>((float)std::stof(value));
}

IOperand const * OperandFactory::createDouble(std::string const &value) const {
	double n(std::stod(value));
	if (n > std::numeric_limits<double>::max())
		throw OperandOverflow();
	if (n < std::numeric_limits<double>::min())
		throw OperandUnderflow();
	return new Operand<double>((double)std::stod(value));
}
