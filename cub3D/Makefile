# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/10/19 19:55:46 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d.a
CUB3D_A = cub3d.a
LIBFT_A = 	libft.a
LIB_DIR = libft
CC = gcc -c 
SRCS = main.c map/check_map.c
//OBJS = ${SRCS:.c=.o}
OBJS = ./*.o

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
				make -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
				mv ${LIBFT_A} ${NAME}
				ar rc ${NAME} ${OBJS}
				ranlib ${NAME}
				
${OBJS}: ${SRCS}
				${CC} ${SRCS}

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
