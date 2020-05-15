#include "Assert.hpp"

Assert::Assert(const std::vector<Value>& args):
	args(args)
{ }

static std::string type(eOperandType t)
{
	switch (t) {
	case (INT8): return "(int8)";
	case (INT16): return "(int16)";
	case (INT32): return "(int32)";
	case (FLOAT): return "(float)";
	default: return "(double)";
	}
}

void Assert::execute(AbstractStack<const IOperand*> & stack) const
{
	const IOperand* op;
	auto it = stack.crbegin();

	if (verbose) cout << "[+] assert (" << args.size() << " value"
			  << (args.size() > 1 ? "s" : "") << ")\n";
	for (const Value& val : args) {
		if (it == stack.crend())
			throw Instruction::StackOutOfRange("assert:"
				" no operand left on stack.");
		op = *it;
		if (verbose) {
			cout << "... " << val.value << " " << type(val.type)
			     << " = " << op->toString() << " "
			     << type(op->getType()) << " ? ";
		}
		if (std::stod(val.value) != std::stod((*it)->toString())) {
			if (verbose) cout << "false\n";
			throw Assert::Exception(Assert::Wrong::value);
		}
		if (val.type != (*it)->getType()) {
			if (verbose) cout << "false\n";
			throw Assert::Exception(Assert::Wrong::type);
		}
		if (verbose) cout << "true\n";
		it++;
	}
}

			   // Exceptions //

Assert::Exception::Exception(enum Wrong cause):
	cause(cause)
{ }

const char* Assert::Exception::what() const throw()
{
	switch (cause) {
	case Wrong::type:
		return "Assertion error: the operands have different types.";
	case Wrong::value:
		return "Assertion error: the operands have different values.";
	default:
		return "Assertion error.";
	}
}
