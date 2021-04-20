/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:28:47 by rprieto-          #+#    #+#             */
/*   Updated: 2021/04/20 15:41:31 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** LINE = string to which characters will be removed.
**
** INDEX = Marks where in *line the characters will be removed.
**
** LENGHT = how many characters will be removed.
**
** Inserts lenght characters of addendum in the string line, creating a new one.
** Returns an index pointing to the character after the inserted bit.
** Removes lenght characters of the string line, creating a new one.
** Returns an index pointing to the character after the removed bit.
**
** NOTE:
** *line is assumed to be malloced.
*/
int	ft_extract(char **line, unsigned int index, unsigned int lenght)
{
	char	*aux;
	int		i;

	aux = malloc(ft_strlen(*line) - lenght + 1);
	if (!aux)
		return (0);
	if (lenght < index + 1)
		i = index + 1 - lenght;
	else
		i = 0;
	ft_strlcpy(aux, *line, i + 1);
	ft_strlcpy(&aux[i], &(*line)[index + 1], ft_strlen(&(*line)[index]));
	free(*line);
	*line = aux;
	return (i);
}
