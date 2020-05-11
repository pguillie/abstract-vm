#include "Exit.hpp"

Exit::Exit() { }

void Exit::execute(AbstractStack<IOperand const *> & stack) const {
	if (verbose) cout << "[+] exit\n";
	while (!stack.empty()) {
		delete stack.top();
		stack.pop();
	}
}

			   // Exceptions //

char const * Exit::Exception::what() const throw() {
	return "no exit instruction.";
}
