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

sources =					\
	main.cpp				\
	parse.cpp				\
	$(addprefix parser/,			\
		Parser.cpp			\
		Lexer.cpp			\
		Token.cpp			\
	)					\
	OperandFactory.cpp			\
	execute.cpp				\
	push.cpp				\
	pop.cpp					\
	dump.cpp				\

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
