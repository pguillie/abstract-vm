NAME = avm

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra

headers =					\
	avm.hpp					\
	$(addprefix parser/,			\
		Parser.hpp			\
		Lexer.hpp			\
		Token.hpp			\
	)					\
	IOperand.hpp				\
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
	parse.cpp				\
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
