#include "Pop.hpp"

Pop::Pop(int count): count(count > 1 ? count : 1) { }

void Pop::execute(AbstractStack<IOperand const *> & stack) const {
	IOperand const * op;

	if (verbose) cout << "[+] pop (" << count << " value"
			  << (count > 1 ? "s" : "") << ")\n";
	for (int c = 0 ; c < count ; c++) {
		op = stack.top();
		if (verbose) cout << "... " << op->toString() << std::endl;
		stack.pop();
		delete op;
	}
}
