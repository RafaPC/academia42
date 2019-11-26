/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:21:58 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/26 10:28:31 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char			*source;
	unsigned int	i;

	i = 0;
	source = (char*)src;
	if (dstsize == 0)
		return (ft_strlen(source));
	if (!dst || !src)
		return (0);
	while (i < dstsize - 1 && source[i])
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(source));
}
