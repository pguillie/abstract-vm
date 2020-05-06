#include <iostream>

#include "avm.hpp"
#include "AbstractStack.hpp"
#include "IOperand.hpp"
#include "instructions/Instruction.hpp"
#include "instructions/Exit.hpp"

void exec_instr(Instruction & i, AbstractStack<IOperand const *> & stack) {
	i.setVerbose();
	try {
		i.execute(stack);
	} catch (std::exception const & e) {
		std::cerr<< e.what() <<std::endl;
		exit(1);
	}
}

void execute(std::queue<Instruction *> instructions) {
	AbstractStack<IOperand const *> stack;
	bool exited = false;

	while (!instructions.empty()) {
		Instruction * i = instructions.front();
		instructions.pop();
		if (!exited) {
			exec_instr(*i, stack);
			exited = (dynamic_cast<Exit *>(i) != NULL);
		}
		delete i;
	}
	if (!exited)
		throw std::runtime_error("No exit instruction encountered");
}
