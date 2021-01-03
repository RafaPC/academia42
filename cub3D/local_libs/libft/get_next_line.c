/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:26:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/17 14:56:12 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int				get_next_line(int fd, char **line)
{
	char			*buffer;
	static t_file	*files[1];
	int				bytes_read;
	char			*aux;
	t_file			*file_buffer;

	if (fd == -1 || line == NULL || BUFFER_SIZE <= 0 ||
	!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!(file_buffer = get_file_buffer(fd, files)))
		return (-1);
	bytes_read = 1;
	if (fill_buffer(file_buffer, &bytes_read, buffer) == -1)
		return (-1);
	if (bytes_read == 0)
		return (last_line(file_buffer, line, files));
	bytes_read = ft_get_index_of(file_buffer->buffer, '\n');
	*line = ft_substr(file_buffer->buffer, 0, bytes_read);
	aux = file_buffer->buffer;
	if (!(file_buffer->buffer = ft_substr(file_buffer->buffer, bytes_read + 1,
	ft_strlen(file_buffer->buffer) - bytes_read)))
		return (-1);
	free(aux);
	return (1);
}

static int		fill_buffer(t_file *file_buffer, int *bytes_read, char *buffer)
{
	char	*aux;

	while (ft_get_index_of(file_buffer->buffer, '\n') == -1 && *bytes_read)
	{
		*bytes_read = read(file_buffer->fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			free(buffer);
			return (-1);
		}
		else if (*bytes_read)
		{
			buffer[*bytes_read] = '\0';
			aux = file_buffer->buffer;
			if (!(file_buffer->buffer =
			ft_strjoin(file_buffer->buffer, buffer)))
			{
				free(aux);
				return (-1);
			}
			free(aux);
		}
	}
	free(buffer);
	return (1);
}

static t_file	*get_file_buffer(int fd, t_file **files)
{
	t_file	*aux;

	aux = *files;
	while (*files != NULL && aux->fd != fd && aux->next != NULL)
		aux = aux->next;
	if (!(aux != 0 && aux->fd == fd) && (*files == NULL || aux->next == NULL))
	{
		if (*files != NULL)
		{
			if (!(aux->next = (t_file *)malloc(sizeof(t_file))))
				return (NULL);
			aux = aux->next;
		}
		else
		{
			if (!(*files = (t_file *)malloc(sizeof(t_file))))
				return (NULL);
			aux = *files;
		}
		aux->fd = fd;
		aux->next = NULL;
		if (!(aux->buffer = ft_strdup("")))
			return (NULL);
	}
	return (aux);
}

static int		last_line(t_file *file_buffer, char **line, t_file *files[1])
{
	if (ft_strlen(file_buffer->buffer))
	{
		*line = ft_substr(file_buffer->buffer, 0,
		ft_strlen(file_buffer->buffer));
		delete_file_struct(file_buffer->fd, files);
	}
	else
	{
		*line = ft_strdup("");
		delete_file_struct(file_buffer->fd, files);
	}
	return (0);
}

static void		delete_file_struct(int fd, t_file *files[1])
{
	t_file			*aux;
	t_file			*iter;

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
		iter = iter->next;
	aux = iter->next;
	free(iter->next->buffer);
	iter->next = aux->next;
	free(aux);
}
