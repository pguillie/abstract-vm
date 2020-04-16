#include <iostream>
#include <fstream>

#include "Parser.hpp"

int main(int argc, char * argv[]) {
	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << " [file]\n";
		return 1;
	}

	Parser parser(argv[1]);
	std::queue<Instruction> instructions;

	try {
		instructions = parser.source();
	} catch (TokErr const & e) {
		parser.show(e);
		return -1;
	} catch (std::exception const & e) {
		std::cerr << e.what()
			  << "\nError: failed to parse the source code.\n";
		return -1;
	}

	while (!instructions.empty())
	{
		Instruction instr = instructions.front();
		std::cout << instr.action << ":";
		std::vector<std::array<std::string, 2>>::iterator it;
		for (it = instr.value.begin() ; it != instr.value.end(); ++it)
			std::cout << it->back() << "(" << it->front() << "),";
		std::cout << std::endl;
		instructions.pop();
	}
	return 0;
}
