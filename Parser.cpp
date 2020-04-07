#include "Parser.hpp"

Parser::Parser(char const * file) {
	if (file) {
		std::ifstream ifs(file);
		if (ifs) {
			source_ << ifs.rdbuf();
			ifs.close();
		}
	} else {
		std::string line;
		while (getline(std::cin, line)) {
			if (line == ";;")
				break;
			source_ << line << std::endl;
		}
		source_.seekg(0, source_.beg);
	}
	lexer_ = new Lexer(source_);
	token_ = lexer_->get();
}

Parser::~Parser() {
	delete lexer_;
}

bool Parser::verify(Token::Type type) {
	if (token_.type() != type)
		return false;
	token_ = lexer_->get();
	return true;
}

void Parser::assert(Token::Type type) {
	if (token_.type() != type)
		throw TokenError(token_);
	token_ = lexer_->get();
}

std::queue<Instruction> Parser::source() {
	std::queue<Instruction> instructions;

	while (true) {
		while (verify(Token::Type::newline)) ;
		if (verify(Token::Type::end))
			break ;
		instructions.push(instr());
		if (verify(Token::Type::end))
			break ;
		assert(Token::Type::newline);
	}
	return instructions;
}

Instruction Parser::instr() {
	Token t = token_;
	Instruction ins;
	int arg;

	if (verify(Token::Type::instr_0))
		arg = 0;
	else if (verify(Token::Type::instr_1))
		arg = 1;
	else
		throw TokenError(token_);
	ins.action = source_.str().substr(t.index(), t.length());
	while (arg--)
		ins.value.push_back(value());
	return ins;
}

std::array<std::string, 2> Parser::value() {
	std::array<std::string, 2> val; // string array to return (ie. Instruction.value)
	Token val_type;			// first token (eg. "int8")
	Token num;			// second token (eg. "142")
	Token::Type num_type;		// second token type (eg. "integer")

	val_type = token_;
	if (verify(Token::Type::integer_t))
		num_type = Token::Type::integer;
	else if (verify(Token::Type::decimal_t))
		num_type = Token::Type::decimal;
	else
		throw TokenError(token_);
	assert(Token::Type::lparen);
	num = token_;
	assert(num_type);
	assert(Token::Type::rparen);
	val.at(0) = source_.str().substr(val_type.index(), val_type.length());
	val.at(1) = source_.str().substr(num.index(), num.length());
	return val;
}
