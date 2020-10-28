# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/10/28 20:43:14 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d.a
CUB3D_A = cub3d.a
LIBFT_A = 	libft.a
LIB_DIR = libft
CC = gcc
SRCS = main.c map/check_map.c map/check_file/check_file_utils.c
//OBJS = ${SRCS:.c=.o}
FLAGS = -Wall -Wextra
OBJS = ./*.o

all: ${NAME}

${NAME}: ${OBJS}
				make -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
				mv ${LIBFT_A} ${NAME}
				${CC} ${SRCS} ${LIB_DIR}/${LIBFT_A} -lmlx -lXext -lX11 -lm
${OBJS}: ${SRCS}
				${CC} -c ${SRCS} -O3

test: ${SRCS} ${NAME}
				gcc ${SRCS} main.c ${NAME}
clean:
		rm -f ${OBJS}
		make -C $(LIB_DIR) clean
		
fclean: clean
		rm -f ${NAME}
		rm -f ${LIBFT_A}
		make -C $(LIB_DIR) fclean
		
re: fclean all

.PHONY:	all clean fclean re test
