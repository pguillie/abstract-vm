#include "Parser.hpp"

Token Parser::assert(TokType type) {
	Token t;

	t = Lexer::get(source_);
	if (t.type() != type)
		throw error(t, type);
	return t;
}

std::queue<Instruction *> Parser::source() {
	std::queue<Instruction *> instructions;
	Instruction * i;

	try {
		while ((i = instruction()))
			instructions.push(i);
	} catch (std::exception const & e) {
		std::cerr<< e.what() <<std::endl;
		throw;
	}
	return instructions;
}

Instruction * Parser::instruction() {
	Token t;
	Instruction * i;
	int c;

	do {
		t = Lexer::get(source_);
	} while (t.type() == TokType::newline);
	if (t.type() == TokType::end)
		return NULL;
	switch (t.type()) {
	case TokType::instr_0: c = 0; break;
	case TokType::instr_1: c = 1; break;
	default: throw error(t, TokType::instr_0); //type can be either one
	}
	i = new Instruction;
	i->name = source_.str().substr(t.index(), t.length());
	while (c--)
		i->args.push_back(value());
	assert(TokType::newline);
	return i;
}

std::array<std::string, 2> Parser::value() {
	Token t;
	TokType type;
	std::array<std::string, 2> val;

	t = Lexer::get(source_);
	switch (t.type()) {
	case TokType::integer_t: type = TokType::integer; break;
	case TokType::decimal_t: type = TokType::decimal; break;
	default: throw error(t, TokType::integer_t);
	}
	val.at(0) = source_.str().substr(t.index(), t.length());
	assert(TokType::lparen);
	t = assert(type);
	val.at(1) = source_.str().substr(t.index(), t.length());
	assert(TokType::rparen);
	return val;
}

SyntaxErr Parser::error(Token token, TokType type) {
	int line, col, line_pos;
	std::string lexeme;

	source_.seekg(0, source_.beg);
	line = 0;
	do {
		line_pos = source_.tellg();
		source_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		line++;
	} while (source_.tellg() < token.index() + 1);
	col = token.index() + 1 - line_pos;
	lexeme = source_.str().substr(token.index(), token.length());
	return SyntaxErr(line, col, token.length(), type, token.type(), lexeme);
}

void Parser::setSource(std::stringstream source) {
	source_.str(source.str());
}

void Parser::printError(std::string file, TokErr const & tok) {
	std::string str;
	int i;

	source_.seekg(0, source_.beg);
	i = tok.line();
	while (--i)
		source_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(source_, str);
	if (!file.empty())
		std::cerr << file << ":";
	std::cerr << tok.line() << ":" << tok.column() << ": "
		  << tok.what() << std::endl
		  << " " << str << std::endl
		  << " " << std::string(tok.column() - 1, ' ')
		  << "^" << std::string(tok.length() - 1, '~')
		  << std::endl;
}

			   // Exceptions //

SyntaxErr::SyntaxErr(int line, int col, int len, TokType expected,
	TokType actual, std::string str):
	line_(line), column_(col), length_(len) {
	std::stringstream ss;

	ss << "error: expected "
	   << Token::toString(expected) << " before " << Token::toString(actual);
	if (actual == TokType::instr_0 || actual == TokType::instr_1
		|| actual == TokType::integer_t || actual == TokType::decimal_t
		|| actual == TokType::integer || actual == TokType::decimal)
		ss << " ‘" << str << "’";
	message_ = ss.str();
}


char const * SyntaxErr::what() const throw() {
	return message_.c_str();
}

int SyntaxErr::line() const {
	return line_;
}

int SyntaxErr::column() const {
	return column_;
}

int SyntaxErr::length() const {
	return length_;
}
