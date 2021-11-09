NAME	= span
SRCS	= main.cpp span.cpp
OBJS	= $(SRCS:.cpp=.o)
CXX		= clang++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

all: $(NAME)

$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re:	fclean all