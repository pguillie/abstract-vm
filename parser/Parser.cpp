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
	{"and", &Parser::avm_and},
	{"or", &Parser::avm_or},
	{"xor", &Parser::avm_xor}
};

Token Parser::assert(Token token, TokType type)
{
	if (token.type() != type)
		throw error(token, type);
	return token;
}

std::queue<Instruction*> Parser::source()
{
	std::queue<Instruction*> instructions;
	Instruction* i;

	while ((i = instruction()))
		instructions.push(i);
	return instructions;
}

Instruction* Parser::instruction()
{
	Token t;
	std::string lexeme;

	do {
		t = Lexer::get(source_);
	} while (t.type() == TokType::newline);
	if (t.type() == TokType::eof)
		return NULL;
	assert(t, TokType::instruction);
	lexeme = source_.str().substr(t.index(), t.length());
	if (instructions.find(lexeme) == instructions.end())
		throw std::out_of_range("Error: unknown instruction.");
	return (this->*instructions.at(lexeme))();
}

Instruction* Parser::avm_push() {
	return new Push(value_args(1));
}

Instruction* Parser::avm_pop()
{
	return new Pop(int_arg());
}

Instruction* Parser::avm_dump()
{
	return new Dump(int_arg());
}

Instruction* Parser::avm_assert()
{
	return new Assert(value_args(1));
}

Instruction* Parser::avm_operation(Operation::Type op)
{
	return new Operation(op, value_args(0));
}

Instruction* Parser::avm_add()
{
	return avm_operation(Operation::Type::add);
}

Instruction* Parser::avm_sub()
{
	return avm_operation(Operation::Type::sub);
}

Instruction* Parser::avm_mul()
{
	return avm_operation(Operation::Type::mul);
}

Instruction* Parser::avm_div()
{
	return avm_operation(Operation::Type::div);
}

Instruction* Parser::avm_mod()
{
	return avm_operation(Operation::Type::mod);
}

Instruction* Parser::avm_and()
{
	return avm_operation(Operation::Type::bw_and);
}

Instruction* Parser::avm_or()
{
	return avm_operation(Operation::Type::bw_or);
}

Instruction* Parser::avm_xor()
{
	return avm_operation(Operation::Type::bw_xor);
}

Instruction* Parser::avm_print()
{
	return new Print(int_arg());
}

Instruction* Parser::avm_exit()
{
	assert(Lexer::get(source_), TokType::newline);
	return new Exit();
}

std::vector<Value> Parser::value_args(unsigned int req)
{
	Token t;
	std::vector<Value> args;

	t = Lexer::get(source_);
	if (!req && t.type() != TokType::type) {
		assert(t, TokType::newline);
		return args;
	}
	args.push_back(value(t));
	t = Lexer::get(source_);
	if (req)
		req--;
	while (t.type() == TokType::comma) {
		t = Lexer::get(source_);
		args.push_back(value(t));
		if (req)
			req--;
		t = Lexer::get(source_);
		if (t.type() == TokType::newline)
			break;
	}
	if (req)
		throw error(t, TokType::comma);
	assert(t, TokType::newline);
	return args;
}

Value Parser::value(Token t)
{
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

int Parser::int_arg()
{
	Token t;
	int arg = 0;

	t = Lexer::get(source_);
	if (t.type() == TokType::integer) {
		arg = std::stoi(source_.str().substr(t.index(), t.length()));
		t = Lexer::get(source_);
	}
	assert(t, TokType::newline);
	return arg;
}

SyntaxErr Parser::error(Token token, TokType type)
{
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

void Parser::setSource(std::stringstream& source)
{
	source_.swap(source);
}

void Parser::printError(std::string file, const TokErr& tok)
{
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
	line_(line), column_(col), length_(len)
{
	std::stringstream ss;

	ss << "error: expected "
	   << Token::toString(expected) << " before " << Token::toString(actual);
	if (actual == TokType::instruction || actual == TokType::type
		|| actual == TokType::integer || actual == TokType::decimal)
		ss << " ‘" << str << "’";
	message_ = ss.str();
}

const char* SyntaxErr::what() const throw()
{
	return message_.c_str();
}

int SyntaxErr::line() const
{
	return line_;
}

int SyntaxErr::column() const
{
	return column_;
}

int SyntaxErr::length() const
{
	return length_;
}
