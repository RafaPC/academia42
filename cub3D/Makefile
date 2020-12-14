# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:19:14 by rprieto-          #+#    #+#              #
#    Updated: 2020/12/14 19:04:33 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CUB3D_A = cub3d.a
LIBFT_A = 	libft.a
LIB_DIR = libft
CC = gcc
SRCS =	main.c \
		render/render_color.c \
		render/draw_things.c \
		render/render.c \
		render/render_sprites.c \
		render/hooks.c \
		render/raycast.c \
		render/sprites_utils.c \
		main_file_utils.c \
		checks/check_file.c \
		checks/check_map.c \
		checks/handle_error.c \
		checks/check_file/check_file_utils.c
SRCSTEST = main_file_utils.c checks/check_map.c checks/check_file/check_file_utils.c checks/handle_error.c render/render_color.c render/render.c render/hooks.c render/raycast.c
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
				${CC} ${FLAGS} -I. -Ilibft ${SRCS} ${CUB3D_A} libftprintf.a ~/Desktop/minilibx-linux/libmlx.a -lXext -lX11 -lm -o ${NAME}
${OBJS}: ${SRCS}
				${CC} ${FLAGS} -c ${SRCS} -O3

test:	fclean
				make -C ../printf
				cp ../printf/libftprintf.a .
				make -C ${LIB_DIR}
				cp ${LIB_DIR}/${LIBFT_A} .
				mv ${LIBFT_A} ${CUB3D_A}
				gcc -I. -Ilibft ${SRCSTEST} ${CUB3D_A} libftprintf.a ~/Desktop/minilibx-linux/libmlx.a -lXext -lX11 -lm -o main.out
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
