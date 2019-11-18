/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:58:49 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/18 17:40:00 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int 	ft_strlen(char *string);
int		ift_checkchar(char c, char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int start;
	unsigned int end;
	unsigned int i;
	char *new_string;

	start = get_limit(s1, set, -1);
	end = get_limit(s1, set, 1);
	new_string = (char*)malloc((end - start) * sizeof(char));
	i = 0;
	while ((i + start) < end)
	{
		new_string[i] = s1[i + start];
		i++;
	}
	return (new_string);
}

int		get_limit(char const *string, char const *set, int flag)
{
	unsigned int position;
	unsigned int sum;

	if (flag == 1)
	{
		sum = 1;
		position = 0;
	}
	else
	{
		sum = -1;
		position = ft_strlen((char*)string) - 1;
	}
	while (string[position] && ft_checkchar(string[position], set) && !position)
		position += sum;
	return (position);
}

int		main(int argc, char const *argv[])
{
	printf("%s", ft_strtrim(argv[1], argv[2]));
	return (0);
}
