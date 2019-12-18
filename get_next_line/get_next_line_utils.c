/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:45:48 by rprieto-          #+#    #+#             */
/*   Updated: 2019/12/18 12:16:57 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*string;

	i = 0;
	string = (char*)s;
	while (string[i])
	{
		if (string[i] == c)
			return (&string[i]);
		i++;
	}
	return (c == '\0') ? (&string[i]) : NULL;
}

char	*ft_strdup(const char *s1)
{
	char *string;
	char *new_string;

	string = (char*)s1;
	if (!(new_string = (char*)malloc((ft_strlen(string) + 1) * sizeof(char))))
		return (NULL);
	else
		return (ft_memcpy(new_string, string, ft_strlen(string) + 1));
}

int		ft_index_of(char *string, char c)
{
	int index;

	index = 0;
	while (string[index])
	{
		if (string[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned int	i;

	i = 0;
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (!s1) ? (char*)s2 : (char*)s1;
	if (!(joined_str = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
	* sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined_str[j++] = s2[i++];
	joined_str[j] = '\0';
	return (joined_str);
}