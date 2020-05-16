#include "Exit.hpp"

Exit::Exit(void)
{ }

Exit::~Exit(void)
{ }

void Exit::execute(AbstractStack<const IOperand*>& stack) const
{
	if (verbose) cout << "[+] exit\n";
	while (!stack.empty()) {
		delete stack.top();
		stack.pop();
	}
}

			   // Exceptions //

Exit::Exception::Exception(void)
{ }

Exit::Exception::~Exception(void)
{ }

const char* Exit::Exception::what() const throw()
{
	return "no exit instruction.";
}
