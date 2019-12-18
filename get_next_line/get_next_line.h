/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:45:17 by rprieto-          #+#    #+#             */
/*   Updated: 2019/12/18 12:41:56 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
	#include <unistd.h>
	#include <fcntl.h>
	#include <stdlib.h>
	#ifndef NULL
		#define NULL 0
	#endif
	/*  Prototipos **/
	int				ft_get_next_line(int fd, char **line);
	void			*ft_memcpy(void *dst, const void *src, size_t n);
	int				ft_index_of(char *string, char c);
	char			*ft_strdup(const char *s1);
	unsigned int	ft_strlen(const char *s);
	char			*ft_strjoin(char const *s1, char const *s2);
	#ifndef BUFFER_SIZE
	# define BUFFER_SIZE 1024
	#endif
#endif