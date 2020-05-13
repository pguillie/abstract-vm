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
	double r = std::stod(rhs.toString());

	if (r == 0)
		throw OperandDomainError("division by 0");
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(), std::to_string(value / r));
}

template <class N>
IOperand const * Operand<N>::operator%(IOperand const & rhs) const {
	double r = std::stod(rhs.toString());

	if (r == 0)
		throw OperandDomainError("modulo by 0");
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(), std::to_string(fmod(value, r)));
}

		       // Bitwise operations //

// float and double are not accepted: error by default.
template <class N>
IOperand const * Operand<N>::operator&(IOperand const & rhs
	__attribute__((__unused__))) const {
	throw OperandDomainError("invalid operand to binary operation");
}

template <class N>
IOperand const * Operand<N>::operator|(IOperand const & rhs
	__attribute__((__unused__))) const {
	throw OperandDomainError("invalid operand to binary operation");
}

template <class N>
IOperand const * Operand<N>::operator^(IOperand const & rhs
	__attribute__((__unused__))) const {
	throw OperandDomainError("invalid operand to binary operation");
}

// Logical AND

// Error if float or double.
template <class N>
std::string const bitwise_and(N val, IOperand const & rhs) {
	if (rhs.getType() == FLOAT || rhs.getType() == DOUBLE)
		throw OperandDomainError("invalid operand to binary operation");
	return std::to_string(val & std::stoi(rhs.toString()));
}

// template specializations for integer types
template <> inline
IOperand const * Operand<int8_t>::operator&(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_and(value, rhs));
}
template <> inline
IOperand const * Operand<short>::operator&(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_and(value, rhs));
}
template <> inline
IOperand const * Operand<int>::operator&(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_and(value, rhs));
}

// Logical OR

// Error if float or double.
template <class N>
std::string const bitwise_or(N val, IOperand const & rhs) {
	if (rhs.getType() == FLOAT || rhs.getType() == DOUBLE)
		throw OperandDomainError("invalid operand to binary operation");
	return std::to_string(val | std::stoi(rhs.toString()));
}

// template specializations for integer types
template <> inline
IOperand const * Operand<int8_t>::operator|(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_or(value, rhs));
}
template <> inline
IOperand const * Operand<short>::operator|(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_or(value, rhs));
}
template <> inline
IOperand const * Operand<int>::operator|(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_or(value, rhs));
}

// Logical XOR

// Error if float or double.
template <class N>
std::string const bitwise_xor(N val, IOperand const & rhs) {
	if (rhs.getType() == FLOAT || rhs.getType() == DOUBLE)
		throw OperandDomainError("invalid operand to binary operation");
	return std::to_string(val ^ std::stoi(rhs.toString()));
}

// template specializations for integer types
template <> inline
IOperand const * Operand<int8_t>::operator^(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_xor(value, rhs));
}
template <> inline
IOperand const * Operand<short>::operator^(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_xor(value, rhs));
}
template <> inline
IOperand const * Operand<int>::operator^(IOperand const & rhs) const {
	return factory.createOperand((getPrecision() < rhs.getPrecision()) ?
		rhs.getType() : getType(),
		bitwise_xor(value, rhs));
}

template <class N>
std::string const & Operand<N>::toString(void) const {
	return str;
};
