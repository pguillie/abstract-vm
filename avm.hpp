#ifndef AVM_H_
#define AVM_H_

#include <map>
#include <string>

#include "IOperand.hpp"
#include "AbstractStack.hpp"
#include "instructions/Instruction.hpp"

bool invocation(char** av, std::map<std::string, std::string>& opt,
	std::string& file);

int interactive(const std::map<std::string, std::string>& opt);

int non_interactive(const std::string file,
	const std::map<std::string, std::string>& opt);

bool execute(Instruction& instruction, AbstractStack<const IOperand*>& stack,
	const std::map<std::string, std::string>& opt);

#endif // AVM_H_
