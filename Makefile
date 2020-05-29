NAME = avm

CXX = clang++
CXXFLAGS = $(include) $(warning) $(version)
include := -I. -I./include/
warning := -Wall -Werror -Wextra
version := -std=c++17


headers =					\
	$(addprefix include/,			\
		avm.hpp				\
		AbstractStack.hpp		\
	)					\
	$(addprefix Operand/,			\
		IOperand.hpp			\
		Operand.hpp			\
		Operand.tpp			\
		OperandExceptions.hpp		\
	)					\
	$(addprefix Parser/,			\
		Parser.hpp			\
		Lexer.hpp			\
		Token.hpp			\
	)					\
	$(addprefix Instruction/,		\
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
	$(addprefix src/,			\
		main.cpp			\
		invocation.cpp			\
		interactive.cpp			\
		non_interactive.cpp		\
		execute.cpp			\
	)					\
	$(addprefix Operand/,			\
		OperandFactory.cpp		\
		OperandExceptions.cpp		\
	)					\
	$(addprefix Parser/,			\
		Parser.cpp			\
		Lexer.cpp			\
		Token.cpp			\
	)					\
	$(addprefix Instruction/,		\
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
