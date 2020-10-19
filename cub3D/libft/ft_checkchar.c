/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:54:24 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/15 12:08:38 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_checkchar(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}
