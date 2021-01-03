/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:03:55 by rprieto-          #+#    #+#             */
/*   Updated: 2019/12/03 19:14:09 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char *s2;

	s2 = s;
	while (n--)
		if (*s2 != (char)c)
			s2++;
		else
			return ((void *)s2);
	return (NULL);
}
