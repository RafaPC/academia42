# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2021/01/02 16:01:24 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CUB3D_A = cub3d.a
LIBFT_A = 	libft.a
LIB_DIR = libft
INCLUDES = -I. -Ilibft -Imlx -I../printf
LIBRARIES = -lXext -lX11 -lm
CC = gcc
SRCS =	main.c								\
		file_reading/check_file.c			\
		file_reading/file_reading_utils.c 	\
		file_reading/read_info.c			\
		file_reading/read_map.c				\
		game/main_game.c					\
		game/init_game_variables.c			\
		game/pixel_utils/put_get_pixel.c	\
		game/pixel_utils/rgb_utils.c		\
		game/drawing_utils.c				\
		game/texture_utils.c				\
		game/render.c						\
		game/raycasting/raycast.c			\
		game/raycasting/raycast_utils.c		\
		game/sprites/sprites_utils.c		\
		game/sprites/render_sprites.c		\
		game/hooks.c						\
		game/movement.c						\
		game/free_memory.c					\
		game/screenshot.c
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
