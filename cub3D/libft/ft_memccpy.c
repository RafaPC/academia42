/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:13:05 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/25 16:07:00 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned int	i;

	i = 0;
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (i < n && (unsigned char)c != source[i])
	{
		dest[i] = source[i];
		i++;
	}
	if (i < n)
	{
		dest[i] = source[i];
		return (&dest[i + 1]);
	}
	return (NULL);
}
