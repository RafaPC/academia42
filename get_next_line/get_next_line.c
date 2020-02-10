/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:16:18 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/10 18:19:48 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	another_function(char *aux, int fd, t_file *file_buffer, int *bytes_read, char  *buffer)
{
	while (ft_strrchr(file_buffer->buffer, '\n') == 0 && *bytes_read)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)//Error al leer
			return (-1);
		if (*bytes_read)
		{
			buffer[*bytes_read] = '\0';
			aux = file_buffer->buffer; //mantiene la referencia a la memoria guardada para mas adelante hacerle un free
			file_buffer->buffer = ft_strjoin(file_buffer->buffer, buffer); //juntamos lo leido a lo anterior
			free(aux);
		}
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char			*buffer;
	static t_file	*files[1];
	int				bytes_read;
	char			*aux;
	t_file			*file_buffer;

	aux = NULL;
	if (fd == -1)
		return (-1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	file_buffer = get_file_buffer(fd, &(files[0]));

	bytes_read = 1;
	//Checkear en la lista si existe elemento con ese fd
	//Si no existe crear uno nuevo y añadirlo al final
	//Si existe...
	if (another_function(aux, fd, file_buffer, &bytes_read, buffer) == -1)
		return (-1);
	if (bytes_read == 0)
	{	
		if (ft_strlen(file_buffer->buffer))
		{
			*line = ft_substr(file_buffer->buffer, 0, ft_strlen(file_buffer->buffer));
			delete_file_struct(fd, files);
			return (0);
		}
		else
		{
			*line = ft_strdup("");
			return (0);
		}
	}
	bytes_read = ft_get_index_of(file_buffer->buffer, '\n'); //leemos hasta el salto de linea
	*line = ft_substr(file_buffer->buffer, 0, bytes_read); //guardamos hasta el salto de linea en "line"
	aux = file_buffer->buffer;
	file_buffer->buffer = ft_substr(file_buffer->buffer, bytes_read + 1, ft_strlen(file_buffer->buffer) - bytes_read); //guardamos desde el salto de línea hasta el final
	free(aux);
	free(buffer);
	return (1);
}

t_file		*get_file_buffer(int fd, t_file *files[1])
{
	t_file *p;

	p = files[0];
	if (files[0] == NULL)
	{
		files[0] = (t_file *)malloc(sizeof(t_file));
		files[0]->next = NULL;
		files[0]->fd = fd;
		files[0]->buffer = ft_strdup("");
		return (files[0]);
	}

	while (p->fd != fd && p->next != NULL)
		p = p->next;
	
	if (p->fd == fd)
		return (p);
	else
	{
		p->next = malloc(sizeof(t_file));
		p->fd = fd;
		p->next->next = NULL;
		p->next->buffer = ft_strdup("");
	}
	return p;
}

void	delete_file_struct(int fd, t_file *files[1])
{
	t_file *aux;
	t_file *iter;

	if (files[0]->fd == fd)
	{
		free(files[0]->buffer);
		aux = files[0]->next;
		free(files[0]);
		files[0] = aux;
		return ;
	}
	iter = files[0];
	while (iter->next->fd != fd)
	{
		iter = iter->next;
	}
	aux = iter->next;
	free(iter->next->buffer);
	iter->next = aux->next;
	free(aux);
}