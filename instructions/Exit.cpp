#include "Exit.hpp"

Exit::Exit()
{ }

void Exit::execute(AbstractStack<const IOperand*> & stack) const
{
	if (verbose) cout << "[+] exit\n";
	while (!stack.empty()) {
		delete stack.top();
		stack.pop();
	}
}

			   // Exceptions //

const char* Exit::Exception::what() const throw()
{
	return "no exit instruction.";
}
