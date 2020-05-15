#include <unistd.h>
#include <queue>

#include "avm.hpp"
#include "parser/Parser.hpp"
#include "OperandExceptions.hpp"

static bool read_file(std::string file, std::iostream& ss)
{
	std::ifstream ifs;

	ifs.open(file);
	if (!ifs.is_open()) {
		std::cerr << "Failed to open file ‘" << file << "’\n";
		return false;
	}
	ss << ifs.rdbuf();
	ifs.close();
	return true;
}

static bool read_stdin(std::iostream& ss)
{
	std::string line;

	do {
		if (isatty(0) && isatty(1))
			std::cout << "> ";
		getline(std::cin, line);
		ss << line << std::endl;
	} while (line != ";;" && std::cin.good());
	if (std::cin.bad()) {
		std::cerr << "Failed to read source from stdin\n";
		return false;
	}
	ss.seekg(0, ss.beg);
	return true;
}

void execution(std::queue<Instruction*> instructions,
	const std::map<std::string, std::string>& opt)
{
	AbstractStack<const IOperand*> stack;
	bool exited = false;

	while (!instructions.empty()) {
		if (!exited)
			exited = execute(*instructions.front(), stack, opt);
		delete instructions.front();
		instructions.pop();
	}
	if (!exited)
		throw Exit::Exception();
}

static bool parsing(const std::string file,
	std::queue<Instruction*>& instructions)
{
	Parser parser;
	std::stringstream ss;
	bool error;

	if (!(file.empty() ? read_stdin(ss) : read_file(file, ss)))
		return false;
	parser.setSource(ss);
	error = false;
	while (true) {
		try {
			instructions = parser.source();
			break;
		} catch (const TokErr& e) {
			parser.printError(file, e);
			error = true;
		}
	}
	return !error;
}

int non_interactive(const std::string file,
	const std::map<std::string, std::string>& opt)
{
	std::queue<Instruction*> instructions;

	if (!parsing(file, instructions))
		return 1;
	try {
		execution(instructions, opt);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
