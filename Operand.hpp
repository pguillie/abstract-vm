#ifndef OPERAND_H_
#define OPERAND_H_

#include <cstdint>
#include <cmath>
#include <sstream>

#include <iostream>

#include "IOperand.hpp"
#include "OperandFactory.hpp"

template <class N>
class Operand: public IOperand {
public:
	Operand(N value):
		value(value), str(stringify(value)) { }
	virtual ~Operand() { }

	int getPrecision(void) const;
	eOperandType getType(void) const;

	IOperand const * operator+(IOperand const & rhs) const;
	IOperand const * operator-(IOperand const & rhs) const;
	IOperand const * operator*(IOperand const & rhs) const;
	IOperand const * operator/(IOperand const & rhs) const;
	IOperand const * operator%(IOperand const & rhs) const;

	std::string const & toString(void) const;

protected:
	N const value;
	std::string const str;
	static OperandFactory const factory;

private:
	std::string stringify(N value);

};

template <class N>
OperandFactory const Operand<N>::factory;

template <class N>
std::string Operand<N>::stringify(N value) {
	std::ostringstream os;

	os << +value;
	return os.str();
}

template <class N>
int Operand<N>::getPrecision(void) const {
	return getType();
}

template <class N>
eOperandType Operand<N>::getType(void) const {
	if (typeid(N) == typeid(int8_t)) return INT8;
	if (typeid(N) == typeid(int16_t)) return INT16;
	if (typeid(N) == typeid(int32_t)) return INT32;
	if (typeid(N) == typeid(float)) return FLOAT;
	return DOUBLE;
}

template <class N>
IOperand const * Operand<N>::operator+(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(value + std::stod(rhs.toString())));
}

template <class N>
IOperand const * Operand<N>::operator-(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(value - std::stod(rhs.toString())));
}

template <class N>
IOperand const * Operand<N>::operator*(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(value * std::stod(rhs.toString())));
}

template <class N>
IOperand const * Operand<N>::operator/(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(value / std::stod(rhs.toString())));
}

template <class N>
IOperand const * Operand<N>::operator%(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(fmod(value, std::stod(rhs.toString()))));
}

template <class N>
std::string const & Operand<N>::toString(void) const {
	return str;
};

#endif // OPERAND_H_
