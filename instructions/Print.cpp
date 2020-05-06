#include "Print.hpp"

Print::Print(int count): count(count ? count : 1) { }

static void print(IOperand const * chr) {
	if (chr->getType() != INT8)
		throw std::runtime_error("Print: not a char");
	cout << (char)std::stoi(chr->toString());
}

void Print::execute(AbstractStack<IOperand const *> & stack) const {
	unsigned int c = (count < 0) ? -count : count;

	if (verbose) cout << "[+] print (" << count << " character"
			  << (count > 1 ? "s" : "") << ")\n";
	if (stack.size() < c)
		throw std::runtime_error("Print: stack too small");
	if (count > 0)
		for (auto it = stack.rbegin(); it != stack.rbegin() + c; it++)
			print(*it);
	else
		for (auto it = stack.end() - c; it != stack.end(); it++)
			print(*it);
	if (verbose) cout << std::endl;
}
