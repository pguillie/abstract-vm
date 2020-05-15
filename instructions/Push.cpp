#include "Push.hpp"

const OperandFactory Push::factory;

Push::Push(const std::vector<Value>& args):
	args(args)
{ }

void Push::execute(AbstractStack<const IOperand*> & stack) const
{
	const IOperand* op;

	if (verbose)
		cout << "[+] push (" << args.size() << " value"
		     << (args.size() > 1 ? "s" : "") << ")\n";
	for (const Value& val : args) {
		op = factory.createOperand(val.type, val.value);
		if (verbose) cout << "... " << op->toString() << std::endl;
		stack.push(op);
	}
}
