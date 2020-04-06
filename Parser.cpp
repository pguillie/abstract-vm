#include "Parser.hpp"

Parser::Parser(Lexer & lexer):
	lexer_(lexer) {
	token_ = lexer_.get();
}

std::queue<Instruction> Parser::source() {
	std::queue<Instruction> instr;

	// Token t;
	// do {
	// 	t = lexer_.get();
	// 	std::cout << t << std::endl;
	// } while (t.type() != Token::Type::end);

	do {
		instr_line();
	} while ((token_ = lexer_.get()).type() == Token::Type::newline);
	if (token_.type() != Token::Type::end)
		throw Token::bad_token(token_.index(), token_.length());
	return instr;
}

Instruction Parser::instr_line() {
	if (token_.type() == Token::Type::instr_0) {
		return {"pop", std::vector<std::array<std::string, 2>>}
	} else if (token_.type() == Token::Type::instr_1) {
		;
	}
}

// std::string Parser::value() {

// }
