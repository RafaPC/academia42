# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/12/30 12:22:33 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CUB3D_A = cub3d.a
LIBFT_A = 	libft.a
LIB_DIR = libft
INCLUDES = -I. -Ilibft -Imlx -I../printf
LIBRARIES = -lXext -lX11 -lm
CC = gcc
SRCS =	main.c					\
		render/render_color.c	\
		render/rgb_utils.c		\
		render/draw_things.c	\
		render/render.c			\
		render/render_sprites.c	\
		render/hooks.c			\
		render/movement.c		\
		render/raycast.c		\
		render/sprites_utils.c	\
		render/free_memory.c	\
		render/screenshot.c		\
		render/raycast_utils.c	\
		main_file_utils.c		\
		checks/check_file.c		\
		checks/check_map.c		\
		checks/handle_error.c	\
		checks/check_file/check_file_utils.c
//OBJS = ${SRCS:.c=.o}
FLAGS = -Wall -Wextra
OBJS = ./*.o

all: ${NAME}

${NAME}:
				make -C ../printf
				cp ../printf/libftprintf.a .
				make bonus -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
				mv ${LIBFT_A} ${CUB3D_A}
				${CC} ${FLAGS} ${INCLUDES} ${SRCS} ${CUB3D_A} libftprintf.a mlx/libmlx.a ${LIBRARIES} -o ${NAME}
${OBJS}: ${SRCS}
				${CC} ${FLAGS} -c ${SRCS} -O3

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
