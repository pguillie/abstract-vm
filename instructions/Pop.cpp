#include "Pop.hpp"

Pop::Pop(int count):
	count(count > 1 ? count : 1)
{ }

void Pop::execute(AbstractStack<const IOperand*> & stack) const
{
	const IOperand* op;

	if (verbose)
		cout << "[+] pop (" << count << " value"
		     << (count > 1 ? "s" : "") << ")\n";
	for (int c = 0 ; c < count ; c++) {
		if (stack.empty())
			throw Instruction::StackOutOfRange("pop: empty stack.");
		op = stack.top();
		if (verbose) cout << "... " << op->toString() << std::endl;
		stack.pop();
		delete op;
	}
}
