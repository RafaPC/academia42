/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:16:24 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/06 12:35:04 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
	# define GET_NEXT_LINE_H

	# include <unistd.h>
	# include <stdlib.h>
	# include <fcntl.h>
	# include <stdio.h>
	# ifndef NULL
		# define NULL 0
	# endif
	#define BUFFER_SIZE 42
	typedef struct	s_file
	{
		int				fd;
		char			*buffer;
		t_file			*next;
	}				t_file;
	int		get_next_line(int fd, char **line);
	size_t	ft_strlen(char *s);
	char	*ft_strdup(char *s1);
	char	*ft_strjoin(char *s1, char *s2);
	char	*ft_strrchr(char *s, int c);
	int		ft_get_index_of(char *string, char c);
	char	*ft_substr(char *s, unsigned int start, size_t len);
#endif