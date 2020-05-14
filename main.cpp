#include <iostream>

#include "avm.hpp"

int main(int argc __attribute__((__unused__)), char * argv[]) {
	std::map<std::string, std::string> opt;
	std::string file;

	if (!invocation(argv, opt, file))
		return 1;
	execute(parse(file));
	return 0;
}
