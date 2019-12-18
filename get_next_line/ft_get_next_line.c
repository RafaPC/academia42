/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:45:02 by rprieto-          #+#    #+#             */
/*   Updated: 2019/12/18 16:11:47 by rprieto-         ###   ########.fr       */
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

int		ft_get_next_line(int fd, char **line)
{
	// char	*buffer[BUFFER_SIZE + 1];
	// char		*pointer;
	// int			bytes_readed;
	// int			index;
	// static char	*table[4096];

	// if (buffer[fd] != NULL)
	// {
	// 	cosa(fd, buffer, line);
	// }
	// else
	// {
	// 	pointer = malloc(BUFFER_SIZE);
	// 	if ((bytes_readed = read(fd, pointer, BUFFER_SIZE)) == -1)
	// 		return (-1);
	// 	if (bytes_readed == 0)
	// 		return (0);
	// 	if(!buffer[fd])
	// 		buffer[fd] = ft_strdup(buffer);
	// 	if ((index = ft_index_of(pointer, '\n')) != -1) //Si entra es porque hay un (como mínimo) un salto de línea en lo que ha leído
	// 	{
	// 		*line = (char*)malloc((index + 1) * sizeof(char));
	// 		ft_memcpy(*line, pointer, index + 1);
	// 		// buffer[fd] = (char*)malloc(ft_strlen(pointer) - index);
	// 		// ft_memcpy(buffer[fd], &pointer[index + 1], ft_strlen(pointer) - index);
	// 	}
	// 	else
	// 	{
	// 		*line = (char*)malloc(BUFFER_SIZE);
	// 		ft_memcpy(*line, pointer, BUFFER_SIZE);
	// 		while()
	// 		{
	// 		}
	// 	}

	// 	free(pointer);
	// }
	return (1);
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
	
	while (!exists_line)
	{
		if((bytes_readed = read(fd, buffer, BUFFER_SIZE)) > 0)			//Entra si ha leído algo
		{
			exists_line = (ft_index_of(buffer, '\n') != -1) ? 1 : 0;
			aux = cadena[fd];
			cadena[fd] = malloc(ft_strlen(cadena[fd]) + ft_strlen(buffer + 1));
			cadena[fd] = ft_strjoin(aux, buffer);
			free(aux);
		}
		else
			return (bytes_readed);
	}
	*line = malloc(ft_index_of(cadena[fd], '\n') + 2);
	bytes_readed = ft_index_of(cadena[fd], '\n');
	ft_memcpy(*line, cadena[fd], bytes_readed);
	aux = cadena[fd];
	cadena[fd] = malloc(ft_strlen(cadena[fd]) - bytes_readed);
	ft_memcpy(cadena[fd], &aux[bytes_readed + 1], ft_strlen(&aux[bytes_readed + 1]) - bytes_readed);
	free(aux);
	return(1);
}

int		main(void)
{
	char	**line;
	int i = 1;
	int fd = open("/Users/rprieto-/Documents/academia42/get_next_line/test.txt", O_RDONLY);
	if (ft_get_next_line2(fd, line) == 1)
		printf("%d-%s", i, *line);
	//printf("%s", *line);
	close(fd);
	return (0);
}
