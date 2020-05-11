#include "Print.hpp"

Print::Print(int count): count(count ? count : 1) { }

static void print(IOperand const * chr) {
	if (chr->getType() != INT8)
		throw Print::TypeException();
	cout << (char)std::stoi(chr->toString());
}

void Print::execute(AbstractStack<IOperand const *> & stack) const {
	unsigned int c = (count < 0) ? -count : count;
	unsigned int size;

	if (verbose) cout << "[+] print (" << count << " character"
			  << (count > 1 ? "s" : "") << ")\n";
	size = stack.size();
	if (size < c) {
		if (verbose)
			cout << "... stack contains only " << size << " value"
			     << (size > 1 ? "s" : "") << ":\n";
		c = size;
	}
	if (count > 0)
		for (auto it = stack.rbegin(); it != stack.rbegin() + c; it++)
			print(*it);
	else
		for (auto it = stack.end() - c; it != stack.end(); it++)
			print(*it);
	if (verbose) cout << std::endl;
}

			   // Exceptions //

char const * Print::TypeException::what() const throw() {
	return "print: operand is not a character.";
}
