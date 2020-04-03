#include <iostream>
#include <fstream>

void parse_file(char const * file);
void parse_stdin();

int main(int argc, char * argv[]) {
	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << " [file]\n";
		return 1;
	}

// parse

	if (argv[1])
		parse_file(argv[1]);
	else
		parse_stdin();

// ////////
// 	try {
// 		Parser p(argv[1]);
// 	} catch (Token::bad_token const & e) {
// 		std::cerr << e.what();
// 		// std::cerr << "(" << e.index() << ", " << e.length() << ")\n";
// 	} catch (std::exception const & e) {
// 		std::cerr << "Error: something went wrong while parsing"
// 			" source code.\n"
// 			  << e.what();
// 		return -1;
// 	}
	return 0;
}
