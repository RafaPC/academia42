# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/04/07 18:01:50 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_printf.a
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
