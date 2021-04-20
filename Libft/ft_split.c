/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:15:03 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/31 09:38:16 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	get_word_count(char *string, char delimiter)
{
	int				i;
	unsigned int	word_count;

	i = 0;
	word_count = 0;
	if (ft_strlen(string) == 0)
		return (0);
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
	unsigned int	word_length;

	word_length = 0;
	while (string[index] && string[(index)++] != delimiter)
		word_length++;
	return (word_length);
}

char	*get_next_word(char *string, unsigned int *index,
	char delimiter, unsigned int *word_size)
{
	char	*word;

	if (!(*index == 0 && string[*index] != delimiter))
	{
		while (string[*index] != delimiter)
			(*index)++;
		while (string[*index] == delimiter)
			(*index)++;
	}
	*word_size = word_length((char *)string, *index, delimiter);
	word = ft_substr(string, *index, *word_size);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char			**phrase;
	char			*word;
	unsigned int	index;
	unsigned int	word_size;
	unsigned int	word_index;

	index = 0;
	word_index = 0;
	if (!s)
		return (NULL);
	phrase = (char **)malloc((get_word_count((char *)s, c) + 1)
			* sizeof(char *));
	if (!phrase)
		return (NULL);
	while (word_index < get_word_count((char *)s, c))
	{
		word = get_next_word((char *)s, &index, c, &word_size);
		if (!word)
			return (NULL);
		index += word_size;
		phrase[word_index++] = word;
	}
	phrase[word_index] = NULL;
	return (phrase);
}
