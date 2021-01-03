/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:18:10 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/29 11:46:36 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *pointer;

	pointer = (unsigned char*)b;
	while (len > 0)
	{
		*(pointer++) = (unsigned char)c;
		len--;
	}
	return (b);
}
