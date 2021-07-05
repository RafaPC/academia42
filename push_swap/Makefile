# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 18:09:12 by rprieto-          #+#    #+#              #
#    Updated: 2021/07/01 20:29:11 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_A = libft.a
CHECKER = checker
PUSH_SWAP = push_swap
SRCS =	instructions.c				\
		utils.c						\
		input_utils.c				\
		sort.c						\
		sort_stack_b.c				\
		sort_stack_a.c				\
		push_swap_utils.c			\
		special_permutations.c
SRCS_BONUS = instructions.c			\
		utils.c						\
		input_utils.c				\
		checker.c

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

bonus: ${CHECKER}
${CHECKER}: ${SRCS_BONUS} ${LIBFT_A}
		${CC} -Ilibft ${CFLAGS} ${SRCS_BONUS} ${LIBFT_A} -o ${CHECKER}

clean:
		${RM} ${OBJS}
fclean:	clean
		${RM} ${CHECKER}
		${RM} ${PUSH_SWAP}
re: fclean all
.PHONY: all re clean fclean