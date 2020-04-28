#include "Lexer.hpp"

static LexicalErr error(std::istream & source, int index, int len) {
	int line, col, line_pos;
	std::string str, lexeme;

	source.seekg(0, source.beg);
	line = 0;
	do {
		line_pos = source.tellg();
		getline(source, str);
		line++;
	} while (source.tellg() < index + 1);
	col = index + 1 - line_pos;
	lexeme = str.substr(col - 1, len);
	return LexicalErr(line, col, len, lexeme);
}

static Token const word(std::istream & source) {
	std::map<std::string, TokType>::const_iterator i;
	std::string str;
	int index = source.tellg();

	while (std::isalnum(source.peek()))
		str += source.get();
	i = Lexer::keywords.find(str);
	if (i == Lexer::keywords.end())
		throw error(source, index, str.length());
	return Token(i->second, index, str.length());
}

static Token const number(std::istream & source) {
	std::string str;
	int index = source.tellg();
	int digit = 0;
	int dot = 0;
	char c;

	if (source.peek() == '-')
		str += source.get();
	while ((c = source.peek())) {
		if (std::isdigit(c))
			digit++;
		else if (c == '.')
			dot++;
		else
			break;
		str += source.get();
	}
	if (digit == 0 || dot > 1)
		throw error(source, index, str.length());
	return Token(dot ? TokType::decimal : TokType::integer, index,
		str.length());
}

Token const Lexer::get(std::istream & source) {
	char c;

	while (std::isblank(source.peek()))
		source.ignore();
	c = source.peek();
	if (c == EOF) {
		return Token(TokType::end, (int)source.tellg());
	} else if (c == '(') {
		source.ignore();
		return Token(TokType::lparen, (int)source.tellg() - 1);
	} else if (c == ')') {
		source.ignore();
		return Token(TokType::rparen, (int)source.tellg() - 1);
	} else if (c == '\n' || c == ';') {
		// to fix: comment starts at the `;'
		source.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return Token(TokType::newline, (int)source.tellg() - 1);
	} else if (std::isalpha(c)) {
		return word(source);
	} else if (std::isdigit(c) || c == '-' || c == '.') {
		return number(source);
	}
	throw error(source, source.tellg(), 1);
}

			   // Exceptions //


LexicalErr::LexicalErr(int line, int col, int len, std::string str):
	line_(line), column_(col), length_(len) {
	std::stringstream ss;
	std::string::iterator i;

	for (i = str.begin(); i != str.end(); i++) {
		if (!std::isgraph(*i))
			*i = '?';
	}
	ss << line_ << ":" << column_ << ": error: unrecognized token ‘" << str
	   << "’";
	message_ = ss.str();
}

char const * LexicalErr::what() const throw() {
	return message_.c_str();
}

int LexicalErr::line() const {
	return line_;
}

int LexicalErr::column() const {
	return column_;
}

int LexicalErr::length() const {
	return length_;
}
