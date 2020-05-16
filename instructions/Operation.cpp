#include "Operation.hpp"

OperandFactory const Operation::factory;

Operation::Operation(enum Type op, const std::vector<Value>& args):
	op(op),
	args(args)
{ }

Operation::~Operation(void)
{ }

static std::string OpeName(Operation::Type op)
{
	switch (op) {
	case (Operation::Type::add): return "add";
	case (Operation::Type::sub): return "sub";
	case (Operation::Type::mul): return "mul";
	case (Operation::Type::div): return "div";
	case (Operation::Type::mod): return "mod";
	case (Operation::Type::bw_and): return "and";
	case (Operation::Type::bw_or): return "or";
	default: return "xor";
	}
}

static std::string OpeSymb(Operation::Type op)
{
	switch (op) {
	case (Operation::Type::add): return " + ";
	case (Operation::Type::sub): return " - ";
	case (Operation::Type::mul): return " * ";
	case (Operation::Type::div): return " / ";
	case (Operation::Type::mod): return " % ";
	case (Operation::Type::bw_and): return " & ";
	case (Operation::Type::bw_or): return " | ";
	default: return " ^ ";
	}
}

Instruction::StackOutOfRange error(Operation::Type op)
{
	std::ostringstream os;

	os << OpeName(op) << ": no operand left on stack.";
	return Instruction::StackOutOfRange(os.str().c_str());
}

void Operation::calc(AbstractStack<const IOperand*>& stack,
	const IOperand* rhs) const
{
	const IOperand* lhs;

	if (stack.empty())
		throw error(op);
	lhs = stack.top();
	if (verbose)
		cout << "..| retrieve 'lhs' from stack: "
		     << lhs->toString() << std::endl;
	stack.top() = (op == Type::add) ? *lhs + *rhs
		: (op == Type::sub) ? *lhs - *rhs
		: (op == Type::mul) ? *lhs * *rhs
		: (op == Type::div) ? *lhs / *rhs
		: (op == Type::mod) ? *lhs % *rhs
		: (op == Type::bw_and) ? *lhs & *rhs
		: (op == Type::bw_or) ? *lhs | *rhs
		: *lhs ^ *rhs;
	if (verbose)
		cout << "..+-> " << lhs->toString() << OpeSymb(op)
		     << rhs->toString() << " = " << stack.top()->toString()
		     << std::endl;
	delete lhs;
}

void Operation::execute(AbstractStack<const IOperand*>& stack) const
{
	auto arg = args.begin();
	const IOperand* rhs;
	std::string loc;

	if (verbose) {
		cout << "[+] " << OpeName(op);
		if (args.size())
			cout << " (" << args.size() << " value"
			     << (args.size() > 1 ? "s" : "") << ")";
		cout << std::endl;
	}
	do {
		if (!args.empty()) {
			rhs = factory.createOperand(arg->type, arg->value);
			loc = "arguments";
			arg++;
		} else {
			if (stack.empty())
				throw error(op);
			rhs = stack.top();
			stack.pop();
			loc = "statck";
		}
		if (verbose)
			cout << "..| retrieve 'rhs' from " << loc << ": "
			     << rhs->toString() << std::endl;
		try {
			calc(stack, rhs);
		} catch (...) {
			delete rhs;
			throw;
		}
		delete rhs;
	} while (arg != args.end());
}
