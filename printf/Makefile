# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/10/14 12:04:21 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
TEST = a.out
CC = gcc -c
SRCS = ft_printf.c ft_printf_utils.c ft_strings.c ft_number.c ft_hex.c
OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
				ar rc ${NAME} ${OBJS}
				ranlib ${NAME}

test: ${TEST}

${OBJS}: ${SRCS}
				${CC} ${CFLAGS} ${SRCS}
${TEST}: ${SRCS} ${NAME} main.c
				gcc ${SRCS} main.c ${NAME}
clean:
		rm -f ${OBJS}
fclean: clean
		rm -f ${NAME} ${OBJS2}
re: fclean all
.PHONY:	all clean fclean
