#include "parser/Parser.hpp"

std::queue<Instruction> parse(std::string source_file) {
	Parser parser(source_file);
	std::queue<Instruction> instructions;

	try {
		instructions = parser.source();
	} catch (TokErr const & e) {
		parser.printError(e);
		exit(1);
	}
	return instructions;
}
