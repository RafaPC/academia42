NAME = animals
SRCS = main.cpp Animal.cpp Cat.cpp Dog.cpp Brain.cpp

all: $(NAME)
$(NAME):	$(SRCS)
	clang++ -Wall -Wextra -Werror $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)