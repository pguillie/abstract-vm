#include <iostream>
#include <fstream>

#include "Lexer.hpp"

using namespace std;

void show(std::ifstream & input) {
	Lexer lexer(input);
	Token tok;

	do {
		tok = lexer.get_token();
		cout << tok << endl;
	} while (tok.getType() != EOI);
}

int main(int argc, char * argv[]) {
	ifstream source;

	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <file>" << endl;
		return 1;
	}
	source.open(argv[1]);
	if (source.is_open()) {
		show(source);
		source.close();
	}
	return 0;
}
