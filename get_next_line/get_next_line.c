/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:16:18 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/04 15:48:29 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char *patata[4095 + 1];
	int			bytes_read;
	char		*aux;

	bytes_read = 1;
	if (!patata[fd])
		patata[fd] = ft_strdup("");  //Inicializar patata a nulo;
	while (ft_strrchr(patata[fd], '\n') == 0 && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)//Error al leer
			return (-1);
		if (bytes_read)
		{
			buffer[bytes_read] = '\0';
			aux = patata[fd]; //mantiene la referencia a la memoria guardada para mas adelante hacerle un free
			patata[fd] = ft_strjoin(patata[fd], buffer); //juntamos lo leido a lo anterior
			free(aux);
		}
	}
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
