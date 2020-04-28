#include "avm.hpp"

int main(int argc, char * argv[]) {
	std::queue<Instruction> instr;

	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << " [file]\n";
		return 1;
	}
	instr = parse(argv[1] ? argv[1] : "");
	while (!instr.empty())
	{
		Instruction i = instr.front();
		std::cout << i.action << ":";
		std::vector<std::array<std::string, 2>>::iterator it;
		for (it = i.value.begin() ; it != i.value.end(); ++it)
			std::cout << it->back() << "(" << it->front() << "),";
		std::cout << std::endl;
		instr.pop();
	}
	return 0;
}
