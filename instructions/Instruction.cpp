#include "Instruction.hpp"

void Instruction::setVerbose(bool on)
{
	verbose = on;
}

			   // Exceptions //

Instruction::StackOutOfRange::StackOutOfRange(const char* what_arg):
	std::out_of_range(what_arg)
{ }

const char* Instruction::StackOutOfRange::what() const throw()
{
	return std::out_of_range::what();
}
