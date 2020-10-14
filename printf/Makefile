# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/10/14 16:10:29 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
LIBFT_A = 	libft.a
LIB_DIR = libft/
TEST = a.out
CC = gcc -c 
SRCS = ft_printf.c ft_printf_utils.c ft_strings.c ft_number.c ft_hex.c
OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
				make -C ${LIB_DIR}
				cp ${LIB_DIR}${LIBFT_A} .
				mv ${LIBFT_A} ${NAME}
				ar rc ${NAME} ${OBJS}
				ranlib ${NAME}

test: ${TEST}

${OBJS}: ${SRCS}
				${CC} ${CFLAGS} ${SRCS}
${TEST}: ${SRCS} ${NAME} main.c
				gcc ${SRCS} main.c ${NAME}
clean:
		rm -f ${OBJS}
		make -C $(LIB_DIR) clean
fclean: clean
		rm -f ${NAME}
		make -C $(LIB_DIR) fclean
re: fclean all
.PHONY:	all clean fclean
