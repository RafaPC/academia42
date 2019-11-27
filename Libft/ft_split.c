/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:15:03 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/27 19:10:21 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

unsigned int	get_word_count(char *string, char delimiter)
{
	int				i;
	unsigned int	word_count;

	i = 0;
	word_count = 0;
	if (i == 0 && string[0] != delimiter)
		word_count++;
	while (string[i])
	{
		if (string[i] == delimiter)
		{
			if (string[i + 1] != delimiter && string[i + 1])
				word_count++;
		}
		i++;
	}
	return (word_count);
}

unsigned int	word_length(char *string, unsigned int index, char delimiter)
{
	unsigned int word_length;

	word_length = 0;
	while (string[index] && string[(index)++] != delimiter)
		word_length++;
	return (word_length);
}

void			go_next_word(char *string, unsigned int *index, char delimiter)
{
	if (!(*index == 0 && string[*index] != delimiter))
	{
		while (string[*index] != delimiter)
			(*index)++;
		while (string[*index] == delimiter)
			(*index)++;
	}
}

char			**ft_split(char const *s, char c)
{
	char			**phrase;
	char			*word;
	unsigned int	index;
	unsigned int	word_size;
	unsigned int	word_index;

	//TODO: si s está vacío tengo que devolver un array con dos NULLS
	//checkear que el get_word_counts() me dice que hay 1 palabra aunque el string esté vacío
	index = 0;
	word_index = 0;
	if (ft_strlen((char*)s) == 0)
	{
		if (!(phrase = (char**)malloc(sizeof(char*) * 2)))
			return (NULL);
		phrase[0] = NULL;
		phrase[1] = NULL;
		return (phrase);
	}
	if (!s)
		return (NULL);
	if (!(phrase = (char**)malloc((get_word_count((char*)s, c) + 1)
		* sizeof(char**))))
		return (NULL);
	while (word_index < get_word_count((char*)s, c))
	{
		go_next_word((char*)s, &index, c);
		word_size = word_length((char*)s, index, c);
		if (!(word = ft_substr(s, index, word_size)))
			return (NULL);
		word = ft_substr(s, index, word_size);
		index += word_size;
		phrase[word_index++] = word;
	}
	phrase[word_index] = NULL;
	return (phrase);
}
