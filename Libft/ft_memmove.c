/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:10:38 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/25 17:14:59 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*source;
	char			*destiny;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	source = (char*)src;
	destiny = dst;
	while (i < len)
	{
		destiny[i] = source[i];
		i++;
	}
	return (dst);
}
