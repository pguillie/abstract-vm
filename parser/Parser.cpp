#include "Parser.hpp"

std::map<std::string, fptr> Parser::instructions = {
	{"push", &Parser::avm_push},
	{"pop", &Parser::avm_pop},
	{"dump", &Parser::avm_dump},
	{"assert", &Parser::avm_assert},
	{"add", &Parser::avm_add},
	{"sub", &Parser::avm_sub},
	{"mul", &Parser::avm_mul},
	{"div", &Parser::avm_div},
	{"mod", &Parser::avm_mod},
	{"print", &Parser::avm_print},
	{"exit", &Parser::avm_exit},
};

Token Parser::assert(Token token, TokType type) {
	if (token.type() != type)
		throw error(token, type);
	return token;
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
	std::string lexeme;

	do {
		t = Lexer::get(source_);
	} while (t.type() == TokType::newline);
	if (t.type() == TokType::eof)
		return NULL;
	assert(t, TokType::instruction);
	lexeme = source_.str().substr(t.index(), t.length());
	return (this->*instructions.at(lexeme))();
}

Instruction * Parser::avm_push() {
	Token t;
	std::vector<Value> args;

	t = Lexer::get(source_);
	do {
		args.push_back(value(t));
		t = Lexer::get(source_);
	} while (t.type() != TokType::newline);
	return new Push(args);
}

Instruction * Parser::avm_pop() {
	Token t;
	int count = 0;

	t = Lexer::get(source_);
	if (t.type() == TokType::integer) {
		count = std::stoi(source_.str().substr(t.index(), t.length()));
		t = Lexer::get(source_);
	}
	assert(t, TokType::newline);
	return new Pop(count);
}

Instruction * Parser::avm_dump() {
	Token t;
	int count = 0;

	t = Lexer::get(source_);
	if (t.type() == TokType::integer) {
		count = std::stoi(source_.str().substr(t.index(), t.length()));
		t = Lexer::get(source_);
	}
	assert(t, TokType::newline);
	return new Dump(count);
}

Instruction * Parser::avm_assert() {
	Token t;
	std::vector<Value> args;

	t = Lexer::get(source_);
	do {
		args.push_back(value(t));
		t = Lexer::get(source_);
	} while (t.type() != TokType::newline && t.type() != TokType::eof);
	return new Assert(args);
}

Instruction * Parser::avm_operation(Operation::Type op) {
	Token t;
	std::vector<Value> args;

	t = Lexer::get(source_);
	while (t.type() == TokType::type) {
		args.push_back(value(t));
		t = Lexer::get(source_);
	}
	assert(t, TokType::newline);
	return new Operation(op, args);
}

Instruction * Parser::avm_add() {
	return avm_operation(Operation::Type::add);
}

Instruction * Parser::avm_sub() {
	return avm_operation(Operation::Type::sub);
}

Instruction * Parser::avm_mul() {
	return avm_operation(Operation::Type::mul);
}

Instruction * Parser::avm_div() {
	return avm_operation(Operation::Type::div);
}

Instruction * Parser::avm_mod() {
	return avm_operation(Operation::Type::mod);
}

Instruction * Parser::avm_print() {
	Token t;
	int count = 0;

	t = Lexer::get(source_);
	if (t.type() == TokType::integer) {
		count = std::stoi(source_.str().substr(t.index(), t.length()));
		t = Lexer::get(source_);
	}
	assert(t, TokType::newline);
	return new Print(count);
}

Instruction * Parser::avm_exit() {
	assert(Lexer::get(source_), TokType::newline);
	return new Exit();
}

Value Parser::value(Token t) {
	Value val;
	std::string type;

	assert(t, TokType::type);
	type = source_.str().substr(t.index(), t.length());
	val.type = type == "int8" ? INT8
		: type == "int16" ? INT16
		: type == "int32" ? INT32
		: type == "float" ? FLOAT
		: DOUBLE;
	assert(Lexer::get(source_), TokType::lparen);
	t = assert(Lexer::get(source_), (type.compare(0, 3, "int") == 0) ?
		TokType::integer : TokType::decimal);
	val.value = source_.str().substr(t.index(), t.length());
	assert(Lexer::get(source_), TokType::rparen);
	return val;
}

SyntaxErr Parser::error(Token token, TokType type) {
	int index, line, col, line_pos;
	std::string lexeme;

	source_.clear();
	index = token.index() + 1;
	if (token.index() == -1)
		index += source_.str().size() + 1;
	source_.seekg(0, source_.beg);
	line = 0;
	do {
		line_pos = source_.tellg();
		source_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		line++;
	} while (source_.tellg() < index && !source_.eof());
	col = index - line_pos;
	if (token.type() == TokType::eof)
		lexeme = "";
	else
		lexeme = source_.str().substr(token.index(), token.length());
	return SyntaxErr(line, col, token.length(), type, token.type(), lexeme);
}

void Parser::setSource(std::stringstream source) {
	source_.str(source.str());
}

void Parser::printError(std::string file, TokErr const & tok) {
	std::string str;
	int i;

	source_.clear();
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
	if (actual == TokType::instruction || actual == TokType::type
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
