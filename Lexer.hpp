#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <istream>
#include <fstream>
#include <string>

enum token_type {
	WORD,
	SEP,
	COMMENT,
	END,
	EOI
};

class Token {
public:
	Token() {};
	Token(enum token_type t, std::string v): type(t), value(v) {}
	virtual ~Token() {}
	Token & operator=(Token const & rhs);

	enum token_type getType() { return type; }
	std::string getValue() { return value; }

	friend std::ostream & operator<<(std::ostream & os, Token const & token);

private:

	enum token_type type;
	std::string value;
};

Token & Token::operator=(Token const & rhs) {
	type = rhs.type;
	value.assign(rhs.value);
	return *this;
}

std::ostream & operator<<(std::ostream & os, Token const & t) {
	os << "Token(" << t.type << ", \"" << t.value << "\")";
	return os;
}

////////////////////////////////////////////////////////////////////////////////

class Lexer {
public:
	Lexer(std::ifstream & input): input(input) {}
	virtual ~Lexer() {}

	Token const get_token(void);

private:
	std::string word();
	std::string comment();

	std::ifstream & input;
};

std::string Lexer::word() {
	std::string w;
	char c;

	while (input.get(c) and (std::isalpha(c)
			or std::isdigit(c)
			or c == '(' or c == ')' or c == '.'))
		w += c;
	return w;
}

std::string Lexer::comment() {
	std::string s;
	char c;

	while (input.get(c) and c != '\n')
		s += c;
	return s;
}

Token const Lexer::get_token() {
	char c;

	c = input.peek();
	if (c == EOF) {
		return Token(EOI, "");
	} else if (std::isalpha(c)) {
		return Token(WORD, word());
	} else if (c == '\n') {
		input.seekg(1, input.cur);
		return Token(SEP, "\n");
	} else if (c == ';') {
		return Token(COMMENT, comment());
	} else {
		std::cerr << "Error: Invalid char -- '" << c << "'\n";
		return Token(EOI, "Error");
	}
}

#endif // LEXER_H_
