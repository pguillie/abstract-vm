#include "Push.hpp"

OperandFactory const Push::factory;

Push::Push(std::vector<Value> const & args): args(args) {
}

void Push::execute(AbstractStack<IOperand const *> & stack) const {
	IOperand const * op;

	if (verbose) cout << "[+] push (" << args.size() << " value"
			  << (args.size() > 1 ? "s" : "") << ")\n";
	for (Value const & val : args) {
		op = factory.createOperand(val.type, val.value);
		if (verbose) cout << "... " << op->toString() << std::endl;
		stack.push(op);
	}
}
