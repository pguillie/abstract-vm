#include "Instruction.hpp"

Instruction::Instruction(void):
	verbose(false)
{ }

Instruction::~Instruction(void)
{ }

void Instruction::setVerbose(bool on)
{
	verbose = on;
}

			   // Exceptions //

Instruction::StackOutOfRange::StackOutOfRange(void):
	std::out_of_range("stack out-of-range")
{ }

Instruction::StackOutOfRange::StackOutOfRange(const char* what_arg):
	std::out_of_range(what_arg)
{ }

Instruction::StackOutOfRange::~StackOutOfRange(void)
{ }

const char* Instruction::StackOutOfRange::what() const throw()
{
	return std::out_of_range::what();
}
