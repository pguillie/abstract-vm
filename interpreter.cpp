#include <iostream>
#include <fstream>

#include "Lexer.hpp"

using namespace std;

void show(istream & input) {
	Lexer lexer(input);
	Token tok;

	do {
		tok = lexer.getNextToken();
		cout << tok << endl;
	} while (tok.getType() != Token::Type::end);
}

int main(int argc, char * argv[]) {
	ifstream in;
//	string source;

	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <file>" << endl;
		return 1;
	}
	in.open(argv[1]);
	if (in.is_open()) {
		// in.seekg(0, std::ios::end);
		// source.resize(in.tellg());
		// in.seekg(0, std::ios::beg);
		// in.read(&source[0], source.size());
		show(in);
		in.close();
	}
	return 0;
}
