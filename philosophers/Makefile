CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS =	main.c			\
		philosopher.c	\
		utils.c			\
		read_parameters.c

all:philo

philo: ${SRCS}
		${CC} ${CFLAGS} -lpthread -I. ${SRCS} -o philo

fclean:
	rm -f philo