#include <map>

#include "avm.hpp"
#include "AbstractStack.hpp"
#include "IOperand.hpp"

typedef void (*fptr)(AbstractStack<IOperand const*>&,
	std::vector<std::array<std::string, 2>>);

std::map<std::string, fptr> const actions = {
	{"push", &avm::push},
	{"pop", &avm::pop},
	{"dump", &avm::dump},
};

void execute(std::queue<Instruction *> instructions) {
	AbstractStack<IOperand const *> stack;
	std::map<std::string, fptr>::const_iterator i;

	while (!instructions.empty()) {
		Instruction * instr = instructions.front();
		std::cout << instr->name << ":";
		for (auto it = instr->args.begin() ; it != instr->args.end(); ++it)
			std::cout<<it->back()<<"("<<it->front()<<"),";
		std::cout << std::endl;
		// rename action to name
		i = actions.find(instr->name);
		if (i == actions.end()) {
			std::cerr << "Instruction not found\n";
			instructions.pop();
			continue;
		}
		try {
			i->second(stack, instr->args);
		} catch (std::exception const & e) {
//		} catch (InterpreterExcept const & ie) {
			std::cerr << e.what() << std::endl;
			exit(2);
		}
		instructions.pop();
	}
}
