#include <iostream>

#include "avm.hpp"
#include "AbstractStack.hpp"
#include "IOperand.hpp"
#include "OperandExceptions.hpp"
#include "instructions/Instruction.hpp"
#include "instructions/Exit.hpp"

bool execute(Instruction& instruction, AbstractStack<const IOperand*>& stack,
	const std::map<std::string, std::string>& opt)
{
	if (opt.count("verbose"))
		instruction.setVerbose();
	try {
		instruction.execute(stack);
	} catch (const Instruction::Exception&) {
		std::cerr << "An instruction error caused the program to stop\n";
		throw;
	} catch (const OperandException&) {
		std::cerr << "An operation error caused the program to stop\n";
		throw;
	}
	try {
		(void)dynamic_cast<Exit&>(instruction);
		return false;
	} catch (...) { }
	return true;
}
