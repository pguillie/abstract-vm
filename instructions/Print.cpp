#include "Print.hpp"

Print::Print(int count): count(count ? count : 1) { }

static void print(IOperand const * chr) {
	if (chr->getType() != INT8)
		throw Print::TypeException();
	cout << (char)std::stoi(chr->toString());
}

void Print::execute(AbstractStack<IOperand const *> & stack) const {
	unsigned int c = (count < 0) ? -count : count;
	auto it = stack.cend();

	if (verbose) cout << "[+] print (" << count << " character"
			  << (count > 1 ? "s" : "") << ")\n";
	if (stack.size() < c)
		throw Instruction::StackOutOfRange("print: the stack"
			" contains too few operands");
	while (c--) {
		it--;
		if (count < 0)
			print(*it);
	}
	if (count > 0)
		for (c = count; c; c--)
			print(*it++);
	if (verbose) cout << std::endl;
}

			   // Exceptions //

char const * Print::TypeException::what() const throw() {
	return "print: operand is not a character.";
}
