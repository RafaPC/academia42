# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2021/01/03 13:58:49 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
CUB3D_A = cub3d.a
LIBFT_A = libft.a
LIB_DIR = libft
INCLUDES = -Ilibft -Imlx -I../printf
LIBRARIES = -lXext -lX11 -lm
CC = gcc
SRCS =	srcs/main.c								\
		srcs/file_reading/check_file.c			\
		srcs/file_reading/file_reading_utils.c 	\
		srcs/file_reading/read_info.c			\
		srcs/file_reading/read_map.c			\
		srcs/game/main_game.c					\
		srcs/game/init_game_variables.c			\
		srcs/game/pixel_utils/put_get_pixel.c	\
		srcs/game/pixel_utils/rgb_utils.c		\
		srcs/game/drawing_utils.c				\
		srcs/game/texture_utils.c				\
		srcs/game/render.c						\
		srcs/game/raycasting/raycast.c			\
		srcs/game/raycasting/raycast_utils.c	\
		srcs/game/sprites/sprites_utils.c		\
		srcs/game/sprites/render_sprites.c		\
		srcs/game/hooks.c						\
		srcs/game/movement.c					\
		srcs/game/free_memory.c					\
		srcs/game/screenshot.c
SRCS_BONUS = srcs/bonus/main.c							\
		srcs/bonus/file_reading/check_file.c			\
		srcs/bonus/file_reading/file_reading_utils.c	\
		srcs/bonus/file_reading/read_info.c				\
		srcs/bonus/file_reading/read_map.c				\
		srcs/bonus/game/main_game.c						\
		srcs/bonus/game/init_game_variables.c			\
		srcs/bonus/game/pixel_utils/put_get_pixel.c		\
		srcs/bonus/game/pixel_utils/rgb_utils.c			\
		srcs/bonus/game/drawing_utils.c					\
		srcs/bonus/game/texture_utils.c					\
		srcs/bonus/game/render.c						\
		srcs/bonus/game/raycasting/raycast.c			\
		srcs/bonus/game/raycasting/raycast_utils.c		\
		srcs/bonus/game/sprites/sprites_utils.c			\
		srcs/bonus/game/sprites/render_sprites.c		\
		srcs/bonus/game/hooks.c							\
		srcs/bonus/game/movement.c						\
		srcs/bonus/game/free_memory.c					\
		srcs/bonus/game/screenshot.c
OBJS =	objs/main.o					\
		objs/check_file.o			\
		objs/file_reading_utils.o	\
		objs/read_info.o			\
		objs/read_map.o				\
		objs/main_game.o			\
		objs/init_game_variables.o	\
		objs/put_get_pixel.o		\
		objs/rgb_utils.o			\
		objs/drawing_utils.o		\
		objs/texture_utils.o		\
		objs/render.o				\
		objs/raycast.o				\
		objs/raycast_utils.o		\
		objs/sprites_utils.o		\
		objs/render_sprites.o		\
		objs/hooks.o				\
		objs/movement.o				\
		objs/free_memory.o			\
		objs/screenshot.o
OBJS_BONUS =	objs/bonus/main.o			\
		objs/bonus/check_file.o				\
		objs/bonus/file_reading_utils.o		\
		objs/bonus/read_info.o				\
		objs/bonus/read_map.o				\
		objs/bonus/main_game.o				\
		objs/bonus/init_game_variables.o	\
		objs/bonus/put_get_pixel.o			\
		objs/bonus/rgb_utils.o				\
		objs/bonus/drawing_utils.o			\
		objs/bonus/texture_utils.o			\
		objs/bonus/render.o					\
		objs/bonus/raycast.o				\
		objs/bonus/raycast_utils.o			\
		objs/bonus/sprites_utils.o			\
		objs/bonus/render_sprites.o			\
		objs/bonus/hooks.o					\
		objs/bonus/movement.o				\
		objs/bonus/free_memory.o			\
		objs/bonus/screenshot.o
FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}:	${OBJS}
				make -C ../printf
				cp ../printf/libftprintf.a .
				make bonus -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
				mv ${LIBFT_A} ${CUB3D_A}
				${CC} ${FLAGS} -Isrcs ${INCLUDES} ${OBJS} ${CUB3D_A} libftprintf.a mlx/libmlx.a ${LIBRARIES} -o ${NAME}
${OBJS}: 	${SRCS}
				${CC} ${FLAGS} -Isrcs ${INCLUDES} -c ${SRCS}
				mv ./*.o objs/
bonus:		${NAME_BONUS}
${NAME_BONUS}:	${OBJS_BONUS}
				make -C ../printf
				cp ../printf/libftprintf.a .
				make bonus -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
				mv ${LIBFT_A} ${CUB3D_A}
				${CC} ${FLAGS} -Isrcs/bonus ${INCLUDES} ${OBJS_BONUS} ${CUB3D_A} libftprintf.a mlx/libmlx.a ${LIBRARIES} -o ${NAME_BONUS}
${OBJS_BONUS}:	${SRCS_BONUS}
				${CC} ${FLAGS} -Isrcs/bonus ${INCLUDES} -c ${SRCS_BONUS}
				mv ./*.o objs/bonus/
clean:
		rm -f ${OBJS}
		rm -f ${OBJS_BONUS}
		make -C ${LIB_DIR} clean
		
fclean: clean
		rm -f ${NAME}
		rm -f ${NAME_BONUS}
		rm -f ${CUB3D_A}
		rm -f ${LIBFT_A}
		rm -f libftprintf.a
		make -C ${LIB_DIR} fclean
		
re: fclean all

.PHONY:	all clean fclean re bonus