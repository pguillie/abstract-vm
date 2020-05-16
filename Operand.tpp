template <class N>
const OperandFactory Operand<N>::factory;

template <class N>
Operand<N>::Operand(N value):
	value(value), str(stringify(value))
{ }

template <class N>
Operand<N>::~Operand(void)
{ }

template <class N>
std::string Operand<N>::stringify(N value)
{
	std::ostringstream os;

	os << +value;
	return os.str();
}

template <class N>
int Operand<N>::getPrecision(void) const
{
	return getType();
}

template <class N>
eOperandType Operand<N>::getType(void) const
{
	if (typeid(N) == typeid(int8_t)) return INT8;
	if (typeid(N) == typeid(int16_t)) return INT16;
	if (typeid(N) == typeid(int32_t)) return INT32;
	if (typeid(N) == typeid(float)) return FLOAT;
	return DOUBLE;
}

template <class N>
const IOperand* Operand<N>::operator+(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(value + std::stod(rhs.toString())));
}

template <class N>
const IOperand* Operand<N>::operator-(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(value - std::stod(rhs.toString())));
}

template <class N>
const IOperand* Operand<N>::operator*(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		std::to_string(value * std::stod(rhs.toString())));
}

template <class N>
const IOperand* Operand<N>::operator/(const IOperand& rhs) const
{
	double r = std::stod(rhs.toString());

	if (r == 0)
		throw OperandDomainError("division by 0");
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(), std::to_string(value / r));
}

template <class N>
const IOperand* Operand<N>::operator%(const IOperand& rhs) const
{
	double r = std::stod(rhs.toString());

	if (r == 0)
		throw OperandDomainError("modulo by 0");
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(), std::to_string(fmod(value, r)));
}

		       // Bitwise operations //

// Logical AND

// Error if float or double.
template <class N>
const IOperand* Operand<N>::operator&(const IOperand& rhs
	__attribute__((__unused__))) const
{
	throw OperandDomainError("invalid operand to binary operation");
}
template <class N>
const std::string bitwise_and(N val, const IOperand& rhs)
{
	if (rhs.getType() == FLOAT || rhs.getType() == DOUBLE)
		rhs & rhs;
	return std::to_string(val & std::stoi(rhs.toString()));
}

// template specializations for integer types
template <> inline
const IOperand* Operand<int8_t>::operator&(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_and(value, rhs));
}
template <> inline
const IOperand* Operand<short>::operator&(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_and(value, rhs));
}
template <> inline
const IOperand* Operand<int>::operator&(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_and(value, rhs));
}

// Logical OR

// Error if float or double.
template <class N>
const IOperand* Operand<N>::operator|(const IOperand& rhs
	__attribute__((__unused__))) const
{
	throw OperandDomainError("invalid operand to binary operation");
}
template <class N>
const std::string bitwise_or(N val, const IOperand& rhs)
{
	if (rhs.getType() == FLOAT || rhs.getType() == DOUBLE)
		rhs & rhs;
	return std::to_string(val | std::stoi(rhs.toString()));
}

// template specializations for integer types
template <> inline
const IOperand* Operand<int8_t>::operator|(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_or(value, rhs));
}
template <> inline
const IOperand* Operand<short>::operator|(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_or(value, rhs));
}
template <> inline
const IOperand* Operand<int>::operator|(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_or(value, rhs));
}

// Logical XOR

// Error if float or double.
template <class N>
const IOperand* Operand<N>::operator^(const IOperand& rhs
	__attribute__((__unused__))) const
{
	throw OperandDomainError("invalid operand to binary operation");
}
template <class N>
const std::string bitwise_xor(N val, const IOperand& rhs)
{
	if (rhs.getType() == FLOAT || rhs.getType() == DOUBLE)
		rhs & rhs;
	return std::to_string(val ^ std::stoi(rhs.toString()));
}

// template specializations for integer types
template <> inline
const IOperand* Operand<int8_t>::operator^(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_xor(value, rhs));
}
template <> inline
const IOperand* Operand<short>::operator^(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_xor(value, rhs));
}
template <> inline
const IOperand* Operand<int>::operator^(const IOperand& rhs) const
{
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_xor(value, rhs));
}

template <class N>
const std::string& Operand<N>::toString(void) const
{
	return str;
};
