/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:04:09 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/30 20:10:19 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_array_clear(void **array, void (*del)(void *))
{
	int	i;

	i = 0;
	if (array)
	{
		if (del)
		{
			while (((char **)array)[i])
				del(array[i++]);
			del(array[i]);
		}
		free(array);
	}
}
