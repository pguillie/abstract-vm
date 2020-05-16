#ifndef IOPERAND_H_
#define IOPERAND_H_

#include <string>

typedef enum {
	INT8,
	INT16,
	INT32,
	FLOAT,
	DOUBLE
} eOperandType;

class IOperand {
public:
	virtual int getPrecision(void) const =0; // Precision of the type of the instance
	virtual eOperandType getType(void) const =0; // Type of the instance

	virtual const IOperand* operator+(const IOperand& rhs) const =0; // Sum
	virtual const IOperand* operator-(const IOperand& rhs) const =0; // Difference
	virtual const IOperand* operator*(const IOperand& rhs) const =0; // Product
	virtual const IOperand* operator/(const IOperand& rhs) const =0; // Quotient
	virtual const IOperand* operator%(const IOperand& rhs) const =0; // Modulo

	virtual const std::string& toString(void) const =0; // String representation of the instance

	virtual ~IOperand(void) { }

	// Bonus
	virtual const IOperand* operator&(const IOperand& rhs) const =0;
	virtual const IOperand* operator|(const IOperand& rhs) const =0;
	virtual const IOperand* operator^(const IOperand& rhs) const =0;
};

#endif // IOPERAND_H
