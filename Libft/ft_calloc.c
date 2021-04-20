/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:05:06 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/30 20:14:21 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;

	array = malloc(count * size);
	if (!array)
		return (NULL);
	if ((int)count == 0 || (int)size == 0)
		return (array);
	ft_bzero(array, count * size);
	return ((void *)array);
}
