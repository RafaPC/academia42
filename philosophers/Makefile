CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
SRCS =	philo/main.c		\
		philo/philosopher.c	\
		read_parameters.c

all:philo

philo: ${SRCS}
		${CC} ${CFLAGS} -lpthread -I. ${SRCS} -o philo/philo