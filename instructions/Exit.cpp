#include "Exit.hpp"

void Exit::clean(AbstractStack<const IOperand*>& stack)
{
	while (!stack.empty()) {
		delete stack.top();
		stack.pop();
	}
}

Exit::Exit(void)
{ }

Exit::~Exit(void)
{ }

void Exit::execute(AbstractStack<const IOperand*>& stack) const
{
	if (verbose) cout << "[+] exit\n";
	clean(stack);
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
