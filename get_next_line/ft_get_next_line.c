/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:45:02 by rprieto-          #+#    #+#             */
/*   Updated: 2019/12/27 16:05:39 by rprieto-         ###   ########.fr       */
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
		*line = (char*)malloc((index + 2) * sizeof(char));
		ft_memcpy(*line, buffer[fd], index + 1);
		(*line)[index + 1] = '\0';
		aux = buffer[fd];
		len = ft_strlen(aux) - index;
		buffer[fd] = (char*)malloc(len * sizeof(char));
		ft_memcpy(buffer[fd], &aux[index + 1], len);
		free(aux);
	}
	else
		buffer[fd] = NULL;
}

int ft_get_next_line2(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*cadena[4096];
	int			bytes_readed;
	char		*aux;
	int			exists_line;
	//Comprobar errores del fd
	// if()
	// {

	// }
	exists_line = 0;
	if (cadena[fd] == NULL)
		cadena[fd] = ft_strdup("");
	if (ft_index_of(cadena[fd], '\n') == -1)
		while (!exists_line)
		{
			if((bytes_readed = read(fd, buffer, BUFFER_SIZE)) > 0)			//Entra si ha leído algo
			{
				buffer[bytes_readed] = '\0';
				exists_line = (ft_index_of(buffer, '\n') != -1) ? 1 : 0;
				aux = cadena[fd];
				cadena[fd] = malloc(ft_strlen(cadena[fd]) + ft_strlen(buffer));
				cadena[fd] = ft_strjoin(aux, buffer);
				free(aux);
			}
			else
				return (bytes_readed);
		}
	if(*line != NULL)
		free(*line);
	*line = malloc(ft_index_of(cadena[fd], '\n') + 2);
	bytes_readed = ft_index_of(cadena[fd], '\n');
	ft_memcpy(*line, cadena[fd], bytes_readed + 1);
	aux = cadena[fd];
	int test = ft_strlen(cadena[fd]) - bytes_readed;
	cadena[fd] = malloc(ft_strlen(cadena[fd]) - bytes_readed);
	ft_memcpy(cadena[fd], &aux[bytes_readed + 1], ft_strlen(&aux[bytes_readed + 1]));
	free(aux);
	return(1);
}

int		main(void)
{
	char	**line;
	int i = 1;
	int fd = open("/Users/rprieto-/Documents/academia42/get_next_line/test.txt", O_RDONLY);
	while(ft_get_next_line2(fd, line) == 1)
		printf("%d-%s", i, *line);
	// if (ft_get_next_line2(fd, line) == 1)
	// 	printf("%d-%s", i, *line);
	// if (ft_get_next_line2(fd, line) == 1)
	// 	printf("%d-%s", i, *line);
	//printf("%s", *line);
	close(fd);
	return (0);
}
