# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/09/08 16:55:37 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
TEST = a.out
CC = gcc -c
SRCS = ft_number.c ft_printf.c ft_printf_utils.c ft_string.c
OBJS = ${SRCS:.c=.o};
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${SRCS}
				${CC} ${SRCS}
				ar rc ${NAME} ${OBJS}

test: ${TEST}

${TEST}: ${SRCS} main.c
				gcc ${SRCS} main.c
clean:
		@rm -f ${OBJS}

fclean: clean
		@rm -f ${NAME}

re: fclean all
.PHONY:	all clean fclean
