#include "avm.hpp"

void avm::pop(AbstractStack<IOperand const *> & stack,
	std::vector<std::array<std::string, 2>> args) {
	if (stack.empty()) {
		// exception here
		std::cout << "pop() on empty stack!\n";
	}
	stack.pop();
	(void)args;
}
