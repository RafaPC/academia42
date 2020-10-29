# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/10/29 13:08:59 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CUB3D_A = cub3d.a
LIBFT_A = 	libft.a
LIB_DIR = libft
CC = gcc
SRCS = main.c map/check_map.c map/check_file/check_file_utils.c render/render_color.c tests.c
//OBJS = ${SRCS:.c=.o}
FLAGS = -Wall -Wextra
OBJS = ./*.o

all: ${NAME}

${NAME}:
				make -C ../printf
				cp ../printf/libftprintf.a .
				make -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
				mv ${LIBFT_A} ${CUB3D_A}
				${CC} ${FLAGS} ${SRCS} ${CUB3D_A} libftprintf.a -lmlx -lXext -lX11 -lm -o ${NAME}
${OBJS}: ${SRCS}
				${CC} ${FLAGS} -c ${SRCS} -O3

# test: ${SRCS} ${NAME}
# 				gcc ${SRCS} main.c ${NAME}
clean:
		rm -f ${OBJS}
		make -C $(LIB_DIR) clean
		
fclean: clean
		rm -f ${NAME}
		rm -f ${CUB3D_A}
		rm -f ${LIBFT_A}
		rm -f libftprintf.a
		make -C $(LIB_DIR) fclean
		
re: fclean all

.PHONY:	all clean fclean re test
