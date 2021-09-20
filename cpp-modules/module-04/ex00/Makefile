NAME = animals
SRCS = main.cpp Animal.cpp Cat.cpp Dog.cpp WrongCat.cpp

all: $(NAME)
$(NAME):	$(SRCS)
	clang++ -Wall -Wextra -Werror $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)