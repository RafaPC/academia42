# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/10/15 17:31:32 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
LIBFT_A = 	libft.a
LIB_DIR = libft/
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
				
${OBJS}: ${SRCS}
				${CC} ${CFLAGS} ${SRCS}

clean:
		rm -f ${OBJS}
		make -C $(LIB_DIR) clean
		
fclean: clean
		rm -f ${NAME}
		make -C $(LIB_DIR) fclean
		
re: fclean all

.PHONY:	all clean fclean re
