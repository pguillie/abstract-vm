#ifndef AVM_H_
#define AVM_H_

#include "AbstractStack.hpp"
#include "IOperand.hpp"
#include "parser/Parser.hpp"

std::queue<Instruction *> parse(std::string file);

void execute(std::queue<Instruction *> instr);

namespace avm {
#define STACK_ARGS \
	AbstractStack<IOperand const*>&, std::vector<std::array<std::string, 2>>

	void push(STACK_ARGS);
	void pop(STACK_ARGS);
	void dump(STACK_ARGS);
	void assert(STACK_ARGS);
	void add(STACK_ARGS);
	void sub(STACK_ARGS);
	void mul(STACK_ARGS);
	void div(STACK_ARGS);
	void mod(STACK_ARGS);
	void print(STACK_ARGS);
	void exit(STACK_ARGS);
}

#endif // AVM_H_
