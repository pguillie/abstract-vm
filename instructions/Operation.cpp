#include "Operation.hpp"

OperandFactory const Operation::factory;

Operation::Operation(enum Type op, std::vector<Value> const & args):
	op(op), args(args) { }

static std::string OpeName(Operation::Type op) {
	switch (op) {
	case (Operation::Type::add): return "add";
	case (Operation::Type::sub): return "sub";
	case (Operation::Type::mul): return "mul";
	case (Operation::Type::div): return "div";
	default: return "mod";
	}
}

static std::string OpeSymb(Operation::Type op) {
	switch (op) {
	case (Operation::Type::add): return " + ";
	case (Operation::Type::sub): return " - ";
	case (Operation::Type::mul): return " * ";
	case (Operation::Type::div): return " / ";
	default: return " % ";
	}
}

Instruction::StackOutOfRange error(Operation::Type op) {
	std::ostringstream os;

	os << OpeName(op) << ": no operand left on stack.";
	return Instruction::StackOutOfRange(os.str().c_str());
}

void Operation::calc(AbstractStack<IOperand const *> & stack,
	IOperand const * rhs) const {
	IOperand const * lhs;

	if (stack.empty())
		throw error(op);
	lhs = stack.top();
	if (verbose) cout << "..| retrieve 'lhs' from stack: "
			  << lhs->toString() << "\n";
	stack.top() = (op == Type::add) ? *lhs + *rhs
		: (op == Type::sub) ? *lhs - *rhs
		: (op == Type::mul) ? *lhs * *rhs
		: (op == Type::div) ? *lhs / *rhs
		: *lhs % *rhs;
	if (verbose) cout << "..+-> " << lhs->toString() << OpeSymb(op)
			  << rhs->toString() << " = " << stack.top()->toString()
			  << std::endl;
	delete lhs;
	delete rhs;
}

void Operation::execute(AbstractStack<IOperand const *> & stack) const {
	IOperand const * rhs;

	if (verbose) {
		cout << "[+] " << OpeName(op);
		if (args.size()) cout << " (" << args.size() << " value"
				      << (args.size() > 1 ? "s" : "") << ")";
		cout << std::endl;
	}
	if (args.empty()) {
		if (stack.empty())
			throw error(op);
		rhs = stack.top();
		stack.pop();
		if (verbose) cout << "..| retrieve 'rhs' from stack: "
				  << rhs->toString() << "\n";
		calc(stack, rhs);
	}
	for (Value const & val : args) {
		rhs = factory.createOperand(val.type, val.value);
		if (verbose) cout << "..| retrieve 'rhs' from arguments: "
				  << rhs->toString() << "\n";
		calc(stack, rhs);
	}
}
