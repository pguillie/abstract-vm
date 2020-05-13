#ifndef OPERAND_H_
#define OPERAND_H_

#include <cstdint>
#include <cmath>
#include <sstream>

#include <iostream>

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "OperandExceptions.hpp"

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
	IOperand const * operator&(IOperand const & rhs) const;
	IOperand const * operator|(IOperand const & rhs) const;
	IOperand const * operator^(IOperand const & rhs) const;

	std::string const & toString(void) const;

protected:
	N const value;
	std::string const str;
	static OperandFactory const factory;

private:
	std::string stringify(N value);

};

#include "Operand.tpp"

#endif // OPERAND_H_
