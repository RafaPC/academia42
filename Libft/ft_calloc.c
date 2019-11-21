/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:05:06 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/21 18:26:55 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char *array;

	if ((int)count <= 0 || (int)size <= 0)
		return (NULL);
	if (!(array = malloc(count * size)))
		return (NULL);
	ft_bzero(array, count);
	return ((void*)array);
}
