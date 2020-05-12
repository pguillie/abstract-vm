#ifndef OPERANDFACTORY_H_
#define OPERANDFACTORY_H_

#include <string>

#include "IOperand.hpp"

class OperandFactory;
typedef IOperand const * (OperandFactory::*createFunc)
	(std::string const & value) const;

class OperandFactory {
public:
	IOperand const * createOperand(eOperandType type,
		std::string const & value) const;

private:
	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

	static createFunc const create[5];
};

#endif // OPERANDFACTORY_H_
