#include <unistd.h>
#include <queue>

#include "avm.hpp"
#include "Parser/Parser.hpp"
#include "Operand/OperandExceptions.hpp"

#define read_source(file, stream)			\
	(((file).empty())				\
		? read_stdin((stream))			\
		: read_file((file), (stream)))

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

static bool parse(const std::string file,
	std::queue<Instruction*>& instructions)
{
	Parser parser;
	std::stringstream ss;
	bool error;

	if (!read_source(file, ss))
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

static void execution(std::queue<Instruction*>& instructions,
	AbstractStack<const IOperand*>& stack,
	const std::map<std::string, std::string>& opt,
	bool proceed)
{

	while (!instructions.empty()) {
		if (proceed)
			proceed = execute(*instructions.front(), stack, opt);
		delete instructions.front();
		instructions.pop();
	}
	if (proceed)
		throw Exit::Exception();
}

int non_interactive(const std::string file,
	const std::map<std::string, std::string>& opt)
{
	AbstractStack<const IOperand*> stack;
	std::queue<Instruction*> instructions;
	bool proceed;

	proceed = parse(file, instructions);
	try {
		execution(instructions, stack, opt, proceed);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		Exit::clean(stack);
		while (!instructions.empty()) {
			delete instructions.front();
			instructions.pop();
		}
		return 1;
	}
	return 0;
}
