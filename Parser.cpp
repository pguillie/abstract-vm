#include "Parser.hpp"

Parser::Parser(Lexer & lexer):
	lexer_(lexer)
{ }

std::queue<Parser::Instruction> Parser::parse() {
	std::queue<Parser::Instruction> instr;

	Token t;
	do {
		t = lexer_.get();
		std::cout << t << std::endl;
	} while (t.type() != Token::Type::end);

	return instr;
}
