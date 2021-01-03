/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:16:24 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/17 20:36:11 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_file
{
	int				fd;
	char			*buffer;
	struct s_file	*next;
}				t_file;

int				get_next_line(int fd, char **line);
static t_file	*get_file_buffer(int fd, t_file **files);
static int		fill_buffer(t_file *file_buffer, int *bytes_read, char *buffer);
static int		last_line(t_file *file_buffer, char **line, t_file *files[1]);
static void		delete_file_struct(int fd, t_file *files[1]);
#endif
