#ifndef AVM_H_
#define AVM_H_

#include <queue>
#include <map>
#include <string>

#include "instructions/Instruction.hpp"

std::queue<Instruction *> parse(std::string file);
bool invocation(char ** av, std::map<std::string, std::string> & opt,
	std::string & file);

void execute(std::queue<Instruction *> instr);

#endif // AVM_H_
