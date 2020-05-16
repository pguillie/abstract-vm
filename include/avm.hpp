#ifndef INCLUDE_AVM_H_
#define INCLUDE_AVM_H_

#include <map>
#include <string>

#include "Operand/IOperand.hpp"
#include "AbstractStack.hpp"
#include "Instruction/Instruction.hpp"

bool invocation(char** av, std::map<std::string, std::string>& opt,
	std::string& file);

int interactive(const std::map<std::string, std::string>& opt);

int non_interactive(const std::string file,
	const std::map<std::string, std::string>& opt);

bool execute(Instruction& instruction, AbstractStack<const IOperand*>& stack,
	const std::map<std::string, std::string>& opt);

#endif // INCLUDE_AVM_H_
