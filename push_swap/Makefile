# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 18:09:12 by rprieto-          #+#    #+#              #
#    Updated: 2021/06/05 13:11:31 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_A = libft.a
NAME = checker
PUSH_SWAP = push_swap
SRCS =	checker_read_instructions.c	\
		checker_operations.c		\
		checker_utils.c				\
		input_utils.c				\
		sort.c
OBJS = ${SRCS:.c=.o};
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: ${NAME}
${NAME}: ${SRCS} checker.c ${LIBFT_A}
		${CC} -Ilibft ${CFLAGS} ${SRCS} checker.c ${LIBFT_A} -o checker
${LIBFT_A}:
		make -C libft
		cp libft/libft.a .
alt:${PUSH_SWAP}
${PUSH_SWAP}: ${SRCS} push_swap.c ${LIBFT_A}
		${CC} -Ilibft ${CFLAGS} ${SRCS} push_swap.c ${LIBFT_A} -o push_swap

clean:
		${RM} ${OBJS}
fclean:	clean
		${RM} ${NAME}
re: fclean all
.PHONY: all re clean fclean