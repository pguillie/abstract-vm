NAME = avm

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra

sources =					\
	main.cpp				\
	parse.cpp				\
	$(addprefix parser/,			\
		Parser.cpp			\
		Lexer.cpp			\
		Token.cpp			\
	)

headers =					\
	$(addprefix parser/,			\
		Parser.hpp			\
		Lexer.hpp			\
		Token.hpp			\
	)

objects = $(sources:%.cpp=%.o)

all: $(NAME)

$(NAME): $(objects)
	$(CXX) -o $@ $^

$(objects): $(headers)

clean:
	$(RM) $(objects)

fclean:
	$(RM) $(objects) $(NAME)

re: fclean all
