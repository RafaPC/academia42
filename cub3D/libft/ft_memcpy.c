/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:57:02 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/22 16:43:16 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
