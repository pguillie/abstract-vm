#include <limits>

#include "OperandFactory.hpp"
#include "Operand.hpp"

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
	if (n > std::numeric_limits<char>::max()
		|| n < std::numeric_limits<char>::min())
		std::cerr << "Exception here\n";
	return new Operand<int8_t>((int8_t)std::stoi(value));
}

IOperand const * OperandFactory::createInt16(std::string const &value) const {
	double n(std::stod(value));
	if (n > std::numeric_limits<char16_t>::max()
		|| n < std::numeric_limits<char16_t>::min())
		std::cerr << "Exception here\n";
	return new Operand<int16_t>((int16_t)std::stoi(value));
}

IOperand const * OperandFactory::createInt32(std::string const &value) const {
	double n(std::stod(value));
	if (n > std::numeric_limits<char32_t>::max()
		|| n < std::numeric_limits<char32_t>::min())
		std::cerr << "Exception here\n";
	return new Operand<int32_t>((int32_t)std::stoi(value));
}

IOperand const * OperandFactory::createFloat(std::string const &value) const {
//	std::cout << "Float: " << value << "\n";
	double n(std::stod(value));
	if (n > std::numeric_limits<float>::max()
		|| n < std::numeric_limits<float>::min())
		std::cerr << "Exception here\n";
	return new Operand<float>((float)std::stof(value));
}

IOperand const * OperandFactory::createDouble(std::string const &value) const {
	// do something here
	return new Operand<double>((double)std::stod(value));
}
