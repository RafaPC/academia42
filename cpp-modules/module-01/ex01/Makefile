NAME = moarbrainz
SRCS = main.cpp Zombie.cpp ZombieHorde.cpp

all: $(NAME)
$(NAME):	$(SRCS)
	clang++ -Wall -Wextra -Werror $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)