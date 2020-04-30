#include <iostream>

#include "avm.hpp"

int main(int argc, char * argv[]) {
	std::string source_file;

	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << " [file]\n";
		return 1;
	}
	if (argv[1])
		source_file = argv[1];
	else
		source_file.clear();
	execute(parse(source_file));
	return 0;
}
