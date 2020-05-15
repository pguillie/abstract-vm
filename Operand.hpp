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

	const IOperand* operator+(const IOperand& rhs) const;
	const IOperand* operator-(const IOperand& rhs) const;
	const IOperand* operator*(const IOperand& rhs) const;
	const IOperand* operator/(const IOperand& rhs) const;
	const IOperand* operator%(const IOperand& rhs) const;
	const IOperand* operator&(const IOperand& rhs) const;
	const IOperand* operator|(const IOperand& rhs) const;
	const IOperand* operator^(const IOperand& rhs) const;

	const std::string& toString(void) const;

protected:
	const N value;
	const std::string str;
	static const OperandFactory factory;

private:
	std::string stringify(N value);

};

#include "Operand.tpp"

#endif // OPERAND_H_
