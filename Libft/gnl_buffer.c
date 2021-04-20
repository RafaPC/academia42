/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:12:36 by aiglesia          #+#    #+#             */
/*   Updated: 2021/03/31 09:31:10 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fill_gnl_buffer(t_gnl_buffer **buffer, char *line)
{
	t_gnl_buffer	*aux;

	if (!*buffer)
	{
		*buffer = ft_calloc(1, sizeof(t_gnl_buffer));
		if (!(*buffer))
			return (0);
		(*buffer)->line = line;
	}
	else
	{
		aux = *buffer;
		while (aux->next)
			aux = aux->next;
		aux->next = ft_calloc(1, sizeof(t_gnl_buffer));
		if (!(aux->next))
			return (0);
		aux->next->line = line;
	}
	return (1);
}

void	free_gnl_buffer(t_gnl_buffer *buffer, t_bool erase_mode)
{
	if (buffer)
	{
		if (erase_mode && buffer->line)
			free(buffer->line);
		if (buffer->next)
			free_gnl_buffer(buffer->next, erase_mode);
		free(buffer);
	}
}

int	gnl_buffer(int fd, int n, t_gnl_buffer **buffer)
{
	char	*line;
	int		continuous;
	int		i;
	int		lenght;

	lenght = 0;
	if (n < 0)
		return (-1);
	continuous = 1;
	if (n)
		continuous = 0;
	while ((n > 0 || continuous))
	{
		i = get_next_line(fd, &line);
		if (!fill_gnl_buffer(buffer, line))
		{
			free_gnl_buffer(*buffer, 1);
			return (-1);
		}
		n--;
		lenght += ft_strlen(line) + 1;
		if (i == 0)
			break ;
	}
	return (lenght);
}

/*
** WARNING: only use if close is allowed!
*/

void	end_get_next_line(int fd)
{
	char	*line;

	close(fd);
	get_next_line(fd, &line);
}
