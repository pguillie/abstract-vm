#include <iostream>

#include "avm.hpp"
#include "AbstractStack.hpp"
#include "IOperand.hpp"
#include "OperandExceptions.hpp"
#include "instructions/Instruction.hpp"
#include "instructions/Exit.hpp"

static void exec_instr(Instruction & i, AbstractStack<IOperand const *> & stack) {
	i.setVerbose();
	try {
		i.execute(stack);
	} catch (Instruction::Exception const &) {
		std::cerr << "An instruction error caused the program to stop.\n";
		throw;
	} catch (OperandException const &) {
		std::cerr << "An operation error caused the program to stop.\n";
		throw;
	}
}

void execute(std::queue<Instruction *> instructions) {
	AbstractStack<IOperand const *> stack;
	bool exited = false;

	try {
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
			throw Exit::Exception();
	} catch (std::exception const & e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
