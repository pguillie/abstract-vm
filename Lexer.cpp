#include "Lexer.hpp"

static Token const word(std::istream & source) {
	std::map<std::string, Token::Type>::const_iterator i;
	std::string w;
	int index = source.tellg();

	while (std::isalnum(source.peek()))
		w += source.get();
	i = Lexer::keywords.find(w);
	if (i == Lexer::keywords.end())
		throw TokenError(Token(Token::Type::none, index, w.length()));
	return Token(i->second, index, w.length());
}

static Token const number(std::istream & source) {
	int index = source.tellg();
	int digit = 0;
	int len;
	Token::Type type;
	char c;

	if (source.peek() == '-')
		source.ignore();
	while (source.get(c) && std::isdigit(c))
		digit++;
	if (c != '.') {
		type = Token::Type::integer;
	} else {
		type = Token::Type::decimal;
		while (std::isdigit(source.get()))
			digit++;
	}
	source.unget();
	len = (int)source.tellg() - index;
	if (!digit)
		throw TokenError(Token(Token::Type::none, index, len));
	return Token(type, index, len);
}

Token const Lexer::get(std::istream & source) {
	char c;

	while (std::isblank(source.peek()))
		source.ignore();
	c = source.peek();
	if (c == EOF) {
		return Token(Token::Type::end, (int)source.tellg());
	} else if (c == '(') {
		source.ignore();
		return Token(Token::Type::lparen, (int)source.tellg() - 1);
	} else if (c == ')') {
		source.ignore();
		return Token(Token::Type::rparen, (int)source.tellg() - 1);
	} else if (c == '\n' || c == ';') {
		source.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return Token(Token::Type::newline, (int)source.tellg() - 1);
	} else if (std::isalpha(c)) {
		return word(source);
	} else if (std::isdigit(c) || c == '-' || c == '.') {
		return number(source);
	}
	throw TokenError(Token(Token::Type::none, source.tellg()));
}
