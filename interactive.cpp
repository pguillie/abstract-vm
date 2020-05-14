#include <unistd.h>

#include "avm.hpp"
#include "parser/Parser.hpp"
#include "OperandExceptions.hpp"

static bool read_stdin(std::iostream& ss)
{
	std::string line;

	if (isatty(0) && isatty(1))
		std::cout << ">>> ";
	getline(std::cin, line);
	if (line == ";;" || !std::cin.good())
		return false;
	ss << line << std::endl;
	ss.seekg(0, ss.beg);
	return true;
}

static Instruction* getInstruction(Parser& parser)
{
	Instruction* instruction;
	std::stringstream ss;

	instruction = NULL;
	while (!instruction) {
		std::stringstream().swap(ss);
		if (!read_stdin(ss))
			return NULL;
		parser.setSource(ss);
		try {
			instruction = parser.instruction();
		} catch (const TokErr& e) {
			parser.printError(std::string(), e);
		}
	}
	return instruction;
}

int interactive(const std::map<std::string, std::string>& opt)
{
	AbstractStack<const IOperand*> stack;
	Parser parser;
	Instruction* instruction;
	bool exited;

	do {
		instruction = getInstruction(parser);
		try {
			if (!instruction)
				throw Exit::Exception();
			exited = execute(*instruction, stack, opt);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return 1;
		}
		delete instruction;
	} while (!exited);
	return 0;
}
