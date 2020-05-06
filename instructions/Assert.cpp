#include "Assert.hpp"

Assert::Assert(std::vector<Value> const & args): args(args) { }

static std::string type(eOperandType t) {
	switch (t) {
	case (INT8): return "(int8)";
	case (INT16): return "(int16)";
	case (INT32): return "(int32)";
	case (FLOAT): return "(float)";
	default: return "(double)";
	}
}

void Assert::execute(AbstractStack<IOperand const *> & stack) const {
	IOperand const * op;
	auto it = stack.crbegin();

	if (verbose) cout << "[+] assert (" << args.size() << " value"
			  << (args.size() > 1 ? "s" : "") << ")\n";
	for (Value const & val : args) {
		if (it == stack.crend())
			throw std::runtime_error("Assert: empty stack!");
		op = *it;
		if (verbose) {
			cout << "... " << val.value << " " << type(val.type)
			     << " = " << op->toString() << " "
			     << type(op->getType()) << " ? ";
		}
		if (val.type != (*it)->getType()) {
			if (verbose) cout << "FALSE\n";
			throw std::runtime_error("Assert: types differ");
		}
		if (std::stod(val.value) != std::stod((*it)->toString())) {
			if (verbose) cout << "FALSE\n";
			throw std::runtime_error("Assert: values differ");
		}
		if (verbose) cout << "TRUE\n";
		it++;
	}
}
