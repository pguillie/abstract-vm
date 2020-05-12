#include "parser/Parser.hpp"

std::stringstream read_source(std::string file) {
	std::stringstream ss;

	if (!file.empty()) {
		std::ifstream ifs(file);
		if (ifs) {
			ss << ifs.rdbuf();
			ifs.close();
		}
	} else {
		std::string line;
		while (getline(std::cin, line)) {
			if (line == ";;") break;
			ss << line << std::endl;
		}
		ss.seekg(0, ss.beg);
	}
	return ss;
}

std::queue<Instruction *> parse(std::string file) {
	Parser parser;
	std::queue<Instruction *> instructions;

	parser.setSource(read_source(file));
	try {
		instructions = parser.source();
	} catch (TokErr const & e) {
		parser.printError(file, e);
		exit(1);
	}
	return instructions;
}
