/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:16:18 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/06 11:47:25 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	another_function(char *aux, int fd, char *patata[4096], int *bytes_read, char buffer[BUFFER_SIZE + 1])
{
	while (ft_strrchr(patata[fd], '\n') == 0 && *bytes_read)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)//Error al leer
			return (-1);
		if (*bytes_read)
		{
			buffer[*bytes_read] = '\0';
			aux = patata[fd]; //mantiene la referencia a la memoria guardada para mas adelante hacerle un free
			patata[fd] = ft_strjoin(patata[fd], buffer); //juntamos lo leido a lo anterior
			free(aux);
		}
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char *patata[4096];
	int			bytes_read;
	char		*aux;

	if(fd == -1)
		return (-1);
	bytes_read = 1;
	if (!patata[fd])
		patata[fd] = ft_strdup("");  //Inicializar patata a nulo;
	if (another_function(aux, fd, patata, &bytes_read, buffer) == -1)
		return (-1);
	if (bytes_read == 0)
	{
		if (ft_strlen(patata[fd]))
		{
			*line = ft_substr(patata[fd], 0, ft_strlen(patata[fd]));
			free(patata[fd]);
			patata[fd] = NULL;
			return (0);
		}
		else
		{
			*line = ft_strdup("");
			return (0);
		}
	}
	bytes_read = ft_get_index_of(patata[fd], '\n'); //leemos hasta el salto de linea
	*line = ft_substr(patata[fd], 0, bytes_read); //guardamos hasta el salto de linea en "line"
	aux = patata[fd];
	patata[fd] = ft_substr(patata[fd], bytes_read + 1, ft_strlen(patata[fd]) - bytes_read); //guardamos desde el salto de línea hasta el final
	free(aux);
	return (1);
}

int main(void)
{
	char *line;
	line = 0;
	int fd;

	fd = open("/Users/rprieto-/Documents/academia42/get_next_line/texto.txt", O_RDONLY);
	while(get_next_line(fd, &line))
	{
		printf("%s\n", line);
	}
	printf("%s\n", line);
	close(fd);
	return 0;
}
