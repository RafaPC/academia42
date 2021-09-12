NAME = account_tests
SRCS = Account.cpp tests.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
$(NAME):	$(SRCS)
	clang++ -Wall -Wextra -Werror $(SRCS) -o $(NAME)

# $(OBJS): $(SRCS)
# 	clang++ -Wall -Wextra -Werror -c $(SRCS)

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)