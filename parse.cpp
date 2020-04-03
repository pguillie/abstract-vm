#include <iostream>

#include "Parser.hpp"

void parse(std::istream & input) {
	Lexer lexer(input);
	Parser parser(lexer);
	std::queue<Parser::Instruction> instr;

	instr = parser.parse();
	while (!instr.empty())
	{
		std::cout << instr.front().name << ' ';
		instr.pop();
	}
}

void parse_file(char const * file) {
	std::ifstream ifs(file);

	parse(ifs);
	ifs.close();
}

void parse_stdin() {
	std::stringstream ss;
	std::string line;

	while (getline(std::cin, line)) {
		if (line == ";;")
			break;
		ss << line << std::endl;
	}
	ss.seekg(0, ss.beg);
	parse(ss);
}
