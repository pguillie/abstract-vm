#include "Lexer.hpp"

Lexer::Lexer(std::istream & input): input(input) {}

Token const Lexer::getNextToken(void) {
	char c;

	while (std::isblank(input.peek()))
		input.ignore();
	c = input.peek();
	switch (c) {
	case EOF:
		return Token(Token::Type::end);
	case '(':
		input.ignore();
		return Token(Token::Type::lparen);
	case ')':
		input.ignore();
		return Token(Token::Type::rparen);
	case '\n':
		input.ignore();
		return Token(Token::Type::sep);
	case ';':
		return comment();
	}
	if (std::isalpha(c))
		return keyword();
	if (std::isdigit(c) || c == '-')
		return value();
	//exception
	return Token(Token::Type::comment);

	// while (input.get(c)) {
	// 	if (std::isblank(c))
	// 		continue;
	// 	if (std::isalpha(c))
	// 		return keyword();
	// 	if (std::isdigit(c) || c == '-')
	// 		return value();
	// 	if (c == '(')
	// 		return Token(Token::Type::lparen);
	// 	if (c == ')')
	// 		return Token(Token::Type::rparen);
	// 	if (c == '\n')
	// 		return Token(Token::Type::sep);
	// 	if (c == ';')
	// 		return comment();
	// 	//exception
	// 	return Token(Token::Type::comment);
	// }
	// return Token(Token::Type::end);
}

Token const Lexer::keyword(void) {
	std::map<std::string, Token::Type>::const_iterator i;
	std::string word;
	int index = input.tellg();

	while (std::isalnum(input.peek()))
		word += input.get();
	i = keywords.find(word);
	if (i == keywords.end()) // exception
		return Token();
	return Token(i->second, index, word.length());
}

Token const Lexer::value(void) {
	int index = input.tellg();
	bool digit= (std::isdigit(input.peek())) ? 1 : 0;
	bool dot = 0;
	char c;

	while (input.get(c)) {
		if (std::isdigit(c))
			digit = 1;
		else if (c == '.' && !dot)
			dot = 1;
		else
			break;
	}
	if (!digit) // exception
		return Token();
	input.unget();
	return Token(dot ? Token::Type::dec_value : Token::Type::int_value,
		index, (int)input.tellg() - index);
}

Token const Lexer::comment(void) {
	int index = input.tellg();

	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return Token(Token::Type::comment, index, (int)input.tellg() - index);
}

std::map<std::string, Token::Type> const Lexer::keywords = {
	{"push", Token::Type::instr1},
	{"pop", Token::Type::instr0},
	{"dump", Token::Type::instr0},
	{"assert", Token::Type::instr1},
	{"add", Token::Type::instr0},
	{"sub", Token::Type::instr0},
	{"mul", Token::Type::instr0},
	{"div", Token::Type::instr0},
	{"mod", Token::Type::instr0},
	{"print", Token::Type::instr0},
	{"exit", Token::Type::instr0},
	{"int8", Token::Type::int_type},
	{"int16", Token::Type::int_type},
	{"int32", Token::Type::int_type},
	{"float", Token::Type::dec_type},
	{"double", Token::Type::dec_type}
};
