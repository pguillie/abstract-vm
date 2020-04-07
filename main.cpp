#include <iostream>
#include <fstream>

#include "Parser.hpp"

int main(int argc, char * argv[]) {
	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << " [file]\n";
		return 1;
	}

	Parser parser(argv[1]);
	std::queue<Instruction> instr;

	try {
		instr = parser.source();
	} catch (TokenError const & e) {
		std::cerr<<"Caught token error:\n";
		std::cerr << e.what() << std::endl;
		return -1;
	} catch (std::exception const & e) {
		std::cerr << e.what() << "Error: something went wrong while the source code.\n";
		return -1;
	}
	while (!instr.empty())
	{
		Instruction curr = instr.front();
		std::cout << curr.action << ":";
		std::vector<std::array<std::string, 2>>::iterator it;
		for (it = curr.value.begin() ; it != curr.value.end(); ++it)
			std::cout << it->back() << "(" << it->front() << "),";
		std::cout << std::endl;
		instr.pop();
	}
	return 0;
}
