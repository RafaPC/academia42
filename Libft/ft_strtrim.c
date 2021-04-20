/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:58:49 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/30 22:02:43 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_limit(char const *string, char const *set, int flag)
{
	int	position;
	int	sum;

	if (flag == 1)
	{
		sum = 1;
		position = 0;
	}
	else
	{
		sum = -1;
		position = ft_strlen((char *)string) - 1;
	}
	while (position != -1 && string[position] && ft_checkchar(string[position],
			(char *)set))
		position += sum;
	return (position);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;
	char			*new_string;

	if (!s1 || !set)
		return (NULL);
	start = get_limit(s1, set, 1);
	end = get_limit(s1, set, -1) + 1;
	if (end == 0)
		return (ft_strdup(""));
	new_string = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	i = 0;
	while ((i + start) < end)
	{
		new_string[i] = s1[i + start];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
