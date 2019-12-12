/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:45:02 by rprieto-          #+#    #+#             */
/*   Updated: 2019/12/12 17:48:22 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

void	static cosa(int fd, char *buffer[BUFFER_SIZE], char **line)
{
	int		index;
	char	*aux;
	int		len;

	if((index = ft_index_of(buffer[fd], '\n')) != -1)
	{
		free(*line);
		*line = (char*)malloc((index + 1) * sizeof(char));
		ft_memcpy(*line, buffer[fd], index + 1);
		aux = buffer[fd];
		len = ft_strlen(aux) - index;
		buffer[fd] = (char*)malloc(len * sizeof(char));
		ft_memcpy(buffer[fd], &aux[index + 1], len);
		free(aux);
	}
}

int		ft_get_next_line(int fd, char **line)
{
	static char	*buffer[BUFFER_SIZE];
	char		*pointer;
	int			bytes_readed;
	int			index;

	if (buffer[fd] != NULL)
	{
		cosa(fd, buffer, line);
	}
	else
	{
		pointer = malloc(BUFFER_SIZE);
		if ((bytes_readed = read(fd, pointer, BUFFER_SIZE)) == -1)
			return (-1);
		if ((index = ft_index_of(pointer, '\n')) != -1)
		{
			*line = (char*)malloc((index + 1) * sizeof(char));
			*line = ft_memcpy(*line, pointer, index + 1);
			buffer[fd] = (char*)malloc(ft_strlen(pointer) - index);
			ft_memcpy(buffer[fd], &pointer[index + 1], ft_strlen(pointer) - index);
		}
		free(pointer);
	}
	return (1);
}

int		main(void)
{
	char	**line;

	int fd = open("/Users/rprieto-/Documents/academia42/get_next_line/test.txt", O_RDONLY);
	while (ft_get_next_line(fd, line) == 1)
		printf("%s", *line);
	printf("%s", *line);
	close(fd);
	return (0);
}
