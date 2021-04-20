/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:09:30 by aiglesia          #+#    #+#             */
/*   Updated: 2021/03/30 20:09:44 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates a memory segment of count * size + 1 and
** null terminates the result.
*/

void	*ft_alloc(size_t count, size_t size)
{
	void	*array;

	array = malloc(count * size + size);
	if (!array)
		return (NULL);
	ft_bzero(array + count * size, size);
	return ((void *)array);
}
