#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <map>

enum token_type {
	INSTR_0,
	INSTR_1,
	TYPE_INT,
	TYPE_DEC,
	INTEGER,
	DECIMAL,
	LPAREN,
	RPAREN,
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
	Token keyword();
	Token number();
	std::string comment();

	std::ifstream & input;
	static std::map<std::string, enum token_type> const keywords;
};

std::map<std::string, enum token_type> const Lexer::keywords = {
	{"push", INSTR_1},
	{"pop", INSTR_0},
	{"dump", INSTR_0},
	{"assert", INSTR_1},
	{"add", INSTR_0},
	{"sub", INSTR_0},
	{"mul", INSTR_0},
	{"div", INSTR_0},
	{"mod", INSTR_0},
	{"print", INSTR_0},
	{"exit", INSTR_0},
	{"int8", TYPE_INT},
	{"int16", TYPE_INT},
	{"int32", TYPE_INT},
	{"float", TYPE_DEC},
	{"double", TYPE_DEC}
};

Token Lexer::keyword() {
	std::string s;
	char c;
	std::map<std::string, enum token_type>::const_iterator i;

	while (input.get(c) && (std::isalpha(c) || std::isdigit(c)))
		s += c;
	input.unget();
	i = keywords.find(s);
	if (i == keywords.end())
		return Token(EOI, "Error: invalid instruction");
	return Token(i->second, i->first);
}

Token Lexer::number() {
	enum token_type t;
	std::string s;
	char c;

	t = INTEGER;
	input.get(c);
	s += c;
	while (input.get(c)) {
		if (c == '.' && t != DECIMAL)
			t = DECIMAL;
		else if (std::isdigit(c))
			;
		else
			break;
		s += c;
	}
	input.unget();
	return Token(t, s);
}

std::string Lexer::comment() {
	std::string s;
	char c;

	while (input.get(c) && c != '\n')
		s += c;
	input.unget();
	return s;
}

Token const Lexer::get_token() {
	char c;

	while (input.get(c) && std::isblank(c))
		;
//	if (c != EOF)
		input.unget();
	if (c == EOF) {
		return Token(EOI, "");
	} else if (std::isalpha(c)) {
		return keyword();
	} else if (std::isdigit(c) || c == '-') {
		return number();
	} else if (c == '(') {
		input.seekg(1, input.cur);
		return Token(LPAREN, "(");
	} else if (c == ')') {
		input.seekg(1, input.cur);
		return Token(RPAREN, ")");
	} else if (c == '\n') {
		input.seekg(1, input.cur);
		return Token(SEP, "\n");
	} else if (c == ';') {
		return Token(COMMENT, comment());
	} else {
		std::cerr << "Error: Invalid char -- '" << c << "' (" << int(c) << ")\n";
		return Token(EOI, "Error");
	}
}

#endif // LEXER_H_
