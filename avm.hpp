#ifndef AVM_H_
#define AVM_H_

#include <queue>

#include "instructions/Instruction.hpp"

std::queue<Instruction *> parse(std::string file);

void execute(std::queue<Instruction *> instr);

#endif // AVM_H_
