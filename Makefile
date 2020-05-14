NAME = avm

CXX = clang++
CXXFLAGS = $(warning) $(version)
warning := -Wall -Werror -Wextra
version := -std=c++2a

headers =					\
	avm.hpp					\
	$(addprefix parser/,			\
		Parser.hpp			\
		Lexer.hpp			\
		Token.hpp			\
	)					\
	IOperand.hpp				\
	Operand.tpp				\
	Operand.hpp				\
	OperandExceptions.hpp			\
	$(addprefix instructions/,		\
		Instruction.hpp			\
		Push.hpp			\
		Pop.hpp				\
		Dump.hpp			\
		Assert.hpp			\
		Operation.hpp			\
		Print.hpp			\
		Exit.hpp			\
	)

sources =					\
	main.cpp				\
	invocation.cpp				\
	interactive.cpp				\
	non_interactive.cpp			\
	execute.cpp				\
	$(addprefix parser/,			\
		Parser.cpp			\
		Lexer.cpp			\
		Token.cpp			\
	)					\
	OperandFactory.cpp			\
	OperandExceptions.cpp			\
	$(addprefix instructions/,		\
		Instruction.cpp			\
		Push.cpp			\
		Pop.cpp				\
		Dump.cpp			\
		Assert.cpp			\
		Operation.cpp			\
		Print.cpp			\
		Exit.cpp			\
	)

objects = $(sources:%.cpp=%.o)

all: $(NAME)

$(NAME): $(objects)
	$(CXX) -o $@ $^

$(objects): Makefile $(headers)

clean:
	$(RM) $(objects)

fclean:
	$(RM) $(NAME) $(objects)

re: fclean all
