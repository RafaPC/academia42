NAME = moarbrainz
SRCS = main.cpp Zombie.cpp newZombie.cpp randomChump.cpp

all: $(NAME)
$(NAME):	$(SRCS)
	clang++ -Wall -Wextra -Werror $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)