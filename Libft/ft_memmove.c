/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:10:38 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/28 17:49:14 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned int	i;

	dest = dst;
	source = (unsigned char *)src;
	i = -1;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dest > source)
		while ((int)(--len) >= 0)
			dest[len] = source[len];
	else
		while (++i < len)
			dest[i] = source[i];
	return (dst);
}
