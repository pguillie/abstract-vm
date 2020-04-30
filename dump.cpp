#include "avm.hpp"

void avm::dump(AbstractStack<IOperand const *> & stack,
	std::vector<std::array<std::string, 2>> args) {
	for (auto it = stack.crbegin(); it != stack.crend(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
	(void)args;
}
