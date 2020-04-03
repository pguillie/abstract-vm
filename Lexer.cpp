#include "Lexer.hpp"

Lexer::Lexer(std::istream & input):
	source_(input)
{ }

// Lexer::Lexer(char const * file) {
// 	if (file) {
// 		fs_.open(file);
// 		input_ = &fs_;
// 	} else {
// 		std::string line;
// 	        while (getline(std::cin, line)) {
// 			if (line == ";;")
// 				break;
// 			ss_ << line << std::endl;
// 		}
// 		ss_.seekg(0, ss_.beg);
// 		input_ = &ss_;
// 	}
// }

// Lexer::~Lexer() {
// 	if (fs_.is_open())
// 		fs_.close();
// }

Token const Lexer::get() {
	char c;

	while (std::isblank(source_.peek()))
		source_.ignore();
	c = source_.peek();
	switch (c) {
	case EOF:
		return Token(Token::Type::end);
	case '(':
		source_.ignore();
		return Token(Token::Type::lparen);
	case ')':
		source_.ignore();
		return Token(Token::Type::rparen);
	case '\n':
		source_.ignore();
		return Token(Token::Type::sep);
	case ';':
		return comment();
	}
	if (std::isalpha(c))
		return word();
	if (std::isdigit(c) || c == '-' || c == '.')
		return number();
	throw Token::bad_token(source_.tellg());
}

Token const Lexer::word() {
	std::map<std::string, Token::Type>::const_iterator i;
	std::string w;
	int index = source_.tellg();

	while (std::isalnum(source_.peek()))
		w += source_.get();
	i = keywords_.find(w);
	if (i == keywords_.end())
		throw Token::bad_token(index, w.length());
	return Token(i->second, index, w.length());
}

Token const Lexer::number() {
	int index = source_.tellg();
	int digit = 0;
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
	if (!digit)
		throw Token::bad_token(index, (int)source_.tellg() - index);
	return Token(type, index, (int)source_.tellg() - index);
}

Token const Lexer::comment() {
	int index = source_.tellg();

	source_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return Token(Token::Type::comment, index, (int)source_.tellg() - index);
}

// Static member variables

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
