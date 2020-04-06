#include "Lexer.hpp"

Lexer::Lexer(std::istream & input):
	source_(input)
{ }

Token const Lexer::get() {
	char c;

	while (std::isblank(source_.peek()))
		source_.ignore();
	c = source_.peek();
	if (c == EOF) {
		return Token(Token::Type::end, (int)source_.tellg());
	} else if (c == '(') {
		source_.ignore();
		return Token(Token::Type::lparen, (int)source_.tellg() - 1);
	} else if (c == ')') {
		source_.ignore();
		return Token(Token::Type::rparen, (int)source_.tellg() - 1);
	} else if (c == '\n' || c == ';') {
		source_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return Token(Token::Type::newline, (int)source_.tellg() - 1);
	} else if (std::isalpha(c)) {
		return word();
	} else if (std::isdigit(c) || c == '-' || c == '.') {
		return number();
	}
	throw TokenError(Token(Token::Type::none, source_.tellg()));
}

Token const Lexer::word() {
	std::map<std::string, Token::Type>::const_iterator i;
	std::string w;
	int index = source_.tellg();

	while (std::isalnum(source_.peek()))
		w += source_.get();
	i = keywords_.find(w);
	if (i == keywords_.end())
		throw TokenError(Token(Token::Type::none, index, w.length()));
	return Token(i->second, index, w.length());
}

Token const Lexer::number() {
	int index = source_.tellg();
	int digit = 0;
	int len;
	Token::Type type;
	char c;

	if (source_.peek() == '-')
		source_.ignore();
	while (source_.get(c) && std::isdigit(c))
		digit++;
	if (c != '.') {
		type = Token::Type::integer;
	} else {
		type = Token::Type::decimal;
		while (std::isdigit(source_.get()))
			digit++;
	}
	source_.unget();
	len = (int)source_.tellg() - index;
	if (!digit)
		throw TokenError(Token(Token::Type::none, index, len));
	return Token(type, index, len);
}

		    // Static member variables //

std::map<std::string, Token::Type> const Lexer::keywords_ = {
	{"push", Token::Type::instr_1},
	{"pop", Token::Type::instr_0},
	{"dump", Token::Type::instr_0},
	{"assert", Token::Type::instr_1},
	{"add", Token::Type::instr_0},
	{"sub", Token::Type::instr_0},
	{"mul", Token::Type::instr_0},
	{"div", Token::Type::instr_0},
	{"mod", Token::Type::instr_0},
	{"print", Token::Type::instr_0},
	{"exit", Token::Type::instr_0},
	{"int8", Token::Type::integer_t},
	{"int16", Token::Type::integer_t},
	{"int32", Token::Type::integer_t},
	{"float", Token::Type::decimal_t},
	{"double", Token::Type::decimal_t}
};
