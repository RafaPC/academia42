/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:15:03 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/19 18:16:37 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

unsigned int	get_word_count(char *string, char delimiter)
{
	int				i;
	unsigned int	word_count;

	i = 0;
	word_count = 0;
	while (string[i])
	{
		if (string[i] != delimiter)
		{
			if (string[i + 1] == delimiter || !string[i + 1])
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

void	go_next_word(char *string, unsigned int *index, char delimiter)
{
	if (!(*index == 0 && string[*index] != delimiter))
	{
		while (string[*index] != delimiter)
			(*index)++;
		while (string[*index] == delimiter)
			(*index)++;
	}
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
	while (word_index < get_word_count((char*)s, c))
	{
		phrase = (char**)malloc((get_word_count((char*)s, c) + 1)
		* sizeof(char**));
		go_next_word((char*)s, &index, c);
		word_size = word_length((char*)s, index, c);
		word = (char*)malloc((word_size + 1) * sizeof(char));
		ft_substr(s, index, word_size);
		phrase[word_index++] = word;
	}
	return (phrase);
}

int		main(int argc, char const *argv[])
{
	char **phrase = ft_split((char*)argv[1], argv[2][0]);
	printf("%s", phrase[0]);
	//TOFIX: el segmentation lo da al intentar printearlo con el for
	/*for (int i = 0; phrase[i]; i++)
	{
		printf("%s", phrase[i]);
	}*/
	return (0);
}
