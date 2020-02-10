/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:16:07 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/06 11:55:07 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	char		*dst;
	size_t		i;

	i = 0;
	dst = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
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

char	*ft_strrchr(char *s, int c)
{
	char	*pointer;
	int		s_len;

	s_len = ft_strlen(s);
	pointer = (char *)s + s_len - 1;
	if (c == '\0')
	{
		pointer++;
		return (pointer);
	}
	while (s_len != 0)
	{
		if (*pointer == c)
		{
			return (pointer);
		}
		s_len--;
		pointer--;
	}
	return (0);
}

int     ft_get_index_of(char *string, char c)
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;

	if (!(dest = (char *)malloc(((sizeof(char)) * (len + 1)))))
		return (NULL);
	if (!s)
		return (NULL);
	if ((start >= (ft_strlen(s))))
		return (ft_strdup(""));
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}