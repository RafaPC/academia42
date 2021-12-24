# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2021/12/24 12:06:48 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
#LOCAL LIBRARIES
MLX_A = local_libs/mlx/libmlx.a
LIBFT_A = libft.a
PRINTF_A = libftprintf.a
#ALL LIBRARIES INTO ONE VARIABLE
LOCAL_LIBS = ${MLX_A} ${LIBFT_A} ${PRINTF_A}
#LIBRARIES DIRECTORIES
LIB_DIR = local_libs/libft
PRINTF_DIR = local_libs/printf
#INCLUDES
INCLUDES = -Ilocal_libs/libft -Ilocal_libs/mlx -Ilocal_libs/printf
#EXTERNAL LIBRARIES (NOT LOCAL)
LIBRARIES = -lXext -lX11 -lm
#COMPILER AND FLAGS
CC = gcc
FLAGS = -Wall -Wextra -Werror
#SOURCE FILES
SRCS =	srcs/main.c								\
		srcs/file_reading/check_file.c			\
		srcs/file_reading/file_reading_utils.c 	\
		srcs/file_reading/error_messages.c		\
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
#BONUS SOURCE FILES
SRCS_BONUS = srcs/bonus/main.c							\
		srcs/bonus/file_reading/check_file.c			\
		srcs/bonus/file_reading/file_reading_utils.c	\
		srcs/bonus/file_reading/error_messages.c		\
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
#OBJECT FILES
OBJS =	objs/main.o					\
		objs/check_file.o			\
		objs/file_reading_utils.o	\
		objs/error_messages.o		\
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
#BONUS OBJECT FILES
OBJS_BONUS =	objs/bonus/main.o			\
		objs/bonus/check_file.o				\
		objs/bonus/file_reading_utils.o		\
		objs/bonus/error_messages.o			\
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


all: ${NAME}

install:
	sudo apt-get install gcc xorg libxext-dev libbsd-dev

${NAME}:	${OBJS} ${LIBFT_A} ${PRINTF_A}
				${CC} ${FLAGS} -Isrcs ${INCLUDES} ${OBJS} ${LOCAL_LIBS} ${LIBRARIES} -o ${NAME}

${OBJS}: 	${SRCS}
				${CC} ${FLAGS} -Isrcs ${INCLUDES} -c ${SRCS}
				mkdir --parents ./objs/
				mv ./*.o objs/

bonus:		${NAME_BONUS}

${NAME_BONUS}:	${OBJS_BONUS} ${LIBFT_A} ${PRINTF_A}
				${CC} ${FLAGS} -Isrcs/bonus ${INCLUDES} ${OBJS_BONUS} ${LOCAL_LIBS} ${LIBRARIES} -o ${NAME_BONUS}

${OBJS_BONUS}:	${SRCS_BONUS}
				${CC} ${FLAGS} -Isrcs/bonus ${INCLUDES} -c ${SRCS_BONUS}
				mkdir --parents ./objs/bonus/
				mv ./*.o objs/bonus/

#HOW TO COMPILE LOCAL LIBRARIES (MLX ALREADY COMPILED)
${LIBFT_A}:
				make bonus -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
${PRINTF_A}:
				make -C ${PRINTF_DIR}
				cp ${PRINTF_DIR}/${PRINTF_A} .

clean:
		rm -f ${LIBFT_A}
		rm -f ${PRINTF_A}
		rm -rf ./objs/
		make clean -C ${LIB_DIR}
		make clean -C ${PRINTF_DIR}

fclean: clean
		rm -f ${NAME}
		rm -f ${NAME_BONUS}
		make fclean -C ${LIB_DIR}
		make fclean -C ${PRINTF_DIR}
		
re: fclean all

.PHONY:	install all clean fclean re bonus