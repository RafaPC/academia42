# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 18:09:12 by rprieto-          #+#    #+#              #
#    Updated: 2021/07/13 21:26:06 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_A = libft.a
CHECKER = checker
PUSH_SWAP = push_swap
SRCS =	instructions.c			\
		utils.c					\
		input_utils.c			\
		sort.c					\
		sort_stack_b.c			\
		sort_stack_a.c			\
		push_swap.c				\
		move_biggest_number_to_a.c
SRCS_BONUS = instructions.c		\
		utils.c					\
		input_utils.c			\
		checker.c

OBJS = ${SRCS:.c=.o};
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all:${PUSH_SWAP}
${PUSH_SWAP}: ${SRCS} ${LIBFT_A}
		${CC} -Ilibft ${CFLAGS} ${SRCS} ${LIBFT_A} -o push_swap

bonus: ${CHECKER}
${CHECKER}: ${SRCS_BONUS} ${LIBFT_A}
		${CC} -Ilibft ${CFLAGS} ${SRCS_BONUS} ${LIBFT_A} -o ${CHECKER}

${LIBFT_A}:
		make -C libft
		cp libft/libft.a .

clean:
		${RM} ${OBJS}
fclean:	clean
		${RM} ${CHECKER}
		${RM} ${PUSH_SWAP}
re: fclean all
.PHONY: all re clean fclean