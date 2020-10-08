# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/10/07 21:08:50 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
TEST = a.out
CC = gcc -c
SRCS = ft_printf.c ft_printf_utils.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${SRCS}
				${CC} ${SRCS}
				ar rc ${NAME} ${OBJS} libft.a

test: ${TEST}

${TEST}: ${SRCS} main.c
				gcc ${SRCS} main.c libft.a
clean:
		@rm -f ${OBJS}

fclean: clean
		@rm -f ${NAME} main a.out

re: fclean all
.PHONY:	all clean fclean
