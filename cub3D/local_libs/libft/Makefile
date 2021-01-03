# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 18:09:12 by rprieto-          #+#    #+#              #
#    Updated: 2020/12/16 16:43:27 by rprieto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
EXTRA = libft.a
SRCS =	ft_atoi.c			\
		ft_bzero.c			\
		ft_isalnum.c		\
		ft_isalpha.c		\
		ft_isascii.c		\
		ft_isdigit.c		\
		ft_isprint.c		\
		ft_memccpy.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_memcpy.c			\
		ft_memmove.c		\
		ft_memset.c			\
		ft_strchr.c			\
		ft_strdup.c			\
		ft_strlcat.c		\
		ft_strlcpy.c		\
		ft_strlen.c			\
		ft_strncmp.c		\
		ft_strnstr.c		\
		ft_strrchr.c		\
		ft_tolower.c		\
		ft_toupper.c		\
		ft_putchar_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\
		ft_putstr_fd.c		\
		ft_itoa.c			\
		ft_calloc.c			\
		ft_split.c			\
		ft_strjoin.c		\
		ft_strmapi.c		\
		ft_substr.c			\
		ft_strtrim.c		\
		ft_isspace.c		\
		ft_get_index_of.c	\
		ft_checkchar.c		\
		ft_nbrlen.c			\
		ft_abs.c			\
		get_next_line.c
OBJS = ${SRCS:.c=.o};
CC = gcc -c
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
BONUS = ft_lstadd_back_bonus.c	\
		ft_lstnew_bonus.c		\
		ft_lstlast_bonus.c		\
		ft_lstadd_front_bonus.c	\
		ft_lstsize_bonus.c		\
		ft_lstdelone_bonus.c	\
		ft_lstiter_bonus.c		\
		ft_lstclear_bonus.c		\
		ft_lstmap_bonus.c		\
		ft_lstmove_backwards.c
OBJS2 = ${BONUS:.c=.o};
all: ${NAME}
${NAME}: ${SRCS}
		${CC} ${CFLAGS} ${SRCS}
		ar rc ${NAME} ${OBJS}
		ranlib ${EXTRA}
bonus: all
		${CC} ${CFLAGS} ${BONUS}
		ar rc ${NAME} ${OBJS2}
		ranlib ${NAME}
clean:
		${RM} ${OBJS}
fclean:	clean
		${RM} ${NAME} ${OBJS2}
re: fclean all
.PHONY:     all re clean fclean bonus