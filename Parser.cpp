#include "Parser.hpp"

Parser::Parser(char const * file) {
	if (file) {
		std::ifstream ifs(file);
		if (ifs) {
			source_ << ifs.rdbuf();
			ifs.close();
		}
		file_ = file;
	} else {
		std::string line;
		while (getline(std::cin, line)) {
			if (line == ";;")
				break;
			source_ << line << std::endl;
		}
		source_.seekg(0, source_.beg);
		file_ = "stdin";
	}
	token_ = Lexer::get(source_);
}

bool Parser::verify(TokType type) {
	if (token_.type() != type)
		return false;
	token_ = Lexer::get(source_);
	return true;
}

void Parser::assert(TokType type) {
	if (token_.type() != type)
		throw error(token_, type);
	token_ = Lexer::get(source_);
}

std::queue<Instruction> Parser::source() {
	std::queue<Instruction> instructions;

	while (true) {
		while (verify(TokType::newline)) ;
		if (verify(TokType::end))
			break ;
		instructions.push(instr());
		if (verify(TokType::end))
			break ;
		assert(TokType::newline);
	}
	return instructions;
}

Instruction Parser::instr() {
	Token t = token_;
	Instruction ins;
	int arg;

	if (verify(TokType::instr_0))
		arg = 0;
	else if (verify(TokType::instr_1))
		arg = 1;
	else
		throw error(token_, TokType::instr_0);
	ins.action = source_.str().substr(t.index(), t.length());
	while (arg--)
		ins.value.push_back(value());
	return ins;
}

std::array<std::string, 2> Parser::value() {
	std::array<std::string, 2> val; // string array to return (ie. Instruction.value)
	Token val_type;			// first token (eg. "int8")
	Token num;			// second token (eg. "142")
	TokType num_type;		// second token type (eg. "integer")

	val_type = token_;
	if (verify(TokType::integer_t))
		num_type = TokType::integer;
	else if (verify(TokType::decimal_t))
		num_type = TokType::decimal;
	else
		throw error(token_, TokType::integer_t);
	assert(TokType::lparen);
	num = token_;
	assert(num_type);
	assert(TokType::rparen);
	val.at(0) = source_.str().substr(val_type.index(), val_type.length());
	val.at(1) = source_.str().substr(num.index(), num.length());
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

void Parser::show(TokErr const & tok) {
	std::string str;
	int i;

	source_.seekg(0, source_.beg);
	i = tok.line();
	while (--i)
		source_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(source_, str);
	std::cerr << file_ << ":" << tok.what() << std::endl
		  << " " << str << std::endl
		  << " " << std::string(tok.column() - 1, ' ')
		  << "^" << std::string(tok.length() - 1, '~')
		  << std::endl;
}

			   // Exceptions //

static std::string type_to_str(TokType type) {
	switch (type) {
	case TokType::instr_0:
		return "instruction";
	case TokType::instr_1:
		return "instruction";
	case TokType::integer_t:
		return "numeric type";
	case TokType::decimal_t:
		return "numeric type";
	case TokType::integer:
		return "integer value";
	case TokType::decimal:
		return "decimal value";
	case TokType::lparen:
		return "parenthese";
	case TokType::rparen:
		return "parenthese";
	case TokType::newline:
		return "newline";
	case TokType::end:
		return "end-of-file";
	default:
		return "unknown";
	}
}

SyntaxErr::SyntaxErr(int line, int col, int len, TokType expected,
	TokType actual, std::string str):
	line_(line), column_(col), length_(len) {
	std::stringstream ss;

	ss << line_ << ":" << column_ << ": error: expected "
	   << type_to_str(expected) << " before "
	   << type_to_str(actual);
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
