/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:41:48 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/26 10:36:25 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	int				j;
	int				k;

	i = 0;
	j = 0;
	k = 0;
	if (!needle[i])
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[k] && ((i + j) < len))
		{
			j++;
			k++;
			if (!needle[k])
				return ((char*)&haystack[i]);
		}
		k = 0;
		j = 0;
		i++;
	}
	return (NULL);
}
