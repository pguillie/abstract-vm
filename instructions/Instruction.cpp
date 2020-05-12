#include "Instruction.hpp"

void Instruction::setVerbose(bool on) {
	verbose = on;
}

			   // Exceptions //

Instruction::StackOutOfRange::StackOutOfRange(char const * what_arg):
	std::out_of_range(what_arg) {
}

char const * Instruction::StackOutOfRange::what() const throw() {
	return std::out_of_range::what();
}
