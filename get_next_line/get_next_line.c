/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:26:21 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/12 12:32:49 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		another_function(t_file *file_buffer, int *bytes_read, char *buffer)
{
	char	*aux;

	while (ft_get_index_of(file_buffer->buffer, '\n') == -1 && *bytes_read)
	{
		*bytes_read = read(file_buffer->fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (-1);
		else if (*bytes_read)
		{
			buffer[*bytes_read] = '\0';
			aux = file_buffer->buffer;
			file_buffer->buffer = ft_strjoin(file_buffer->buffer, buffer);
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

	if (fd == -1 || line == NULL || BUFFER_SIZE <= 0 ||
	!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	file_buffer = get_file_buffer(fd, files);
	bytes_read = 1;
	if (another_function(file_buffer, &bytes_read, buffer) == -1)
		return (-1);
	if (bytes_read == 0)
		return (get_next_line_utils(file_buffer, line, files));
	bytes_read = ft_get_index_of(file_buffer->buffer, '\n');
	*line = ft_substr(file_buffer->buffer, 0, bytes_read);
	aux = file_buffer->buffer;
	file_buffer->buffer = ft_substr(file_buffer->buffer, bytes_read + 1,
	ft_strlen(file_buffer->buffer) - bytes_read);
	free(aux);
	free(buffer);
	return (1);
}

int		get_next_line_utils(t_file *file_buffer, char **line, t_file *files[1])
{
	if (ft_strlen(file_buffer->buffer))
	{
		*line = ft_substr(file_buffer->buffer, 0,
		ft_strlen(file_buffer->buffer));
		delete_file_struct(file_buffer->fd, files);
	}
	else
		*line = ft_strdup("");
	return (0);
}

t_file	*get_file_buffer(int fd, t_file **files)
{
	t_file	*aux;

	if (*files == NULL)
	{
		*files = (t_file *)malloc(sizeof(t_file));
		(*files)->next = NULL;
		(*files)->fd = fd;
		(*files)->buffer = ft_strdup("");
		return (*files);
	}
	aux = files[0];
	while (aux->fd != fd && aux->next != NULL)
		aux = aux->next;
	if (aux->fd == fd)
		return (aux);
	else
	{
		aux->next = malloc(sizeof(t_file));
		aux->next->fd = fd;
		aux->next->next = NULL;
		aux->next->buffer = ft_strdup("");
	}
	return (aux);
}

void	delete_file_struct(int fd, t_file *files[1])
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
	{
		iter = iter->next;
	}
	aux = iter->next;
	free(iter->next->buffer);
	iter->next = aux->next;
	free(aux);
}

// int main(void)
// {
// 	char *line;
// 	line = 0;
// 	int fd;

// 	fd = open("/Users/rprieto-/Documents/academia42/get_next_line/texto.txt", O_RDONLY);
// 	while(get_next_line(fd, &line))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	printf("%s\n", line);
// 	close(fd);
// 	// int x = getchar();
// 	return 0;
// }