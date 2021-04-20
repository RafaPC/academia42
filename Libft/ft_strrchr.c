/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:50:14 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/30 22:01:08 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last_ocurrence;
	char	*string;

	string = (char *)s;
	i = 0;
	last_ocurrence = -1;
	while (string[i])
	{
		if (string[i] == c)
			last_ocurrence = i;
		i++;
	}
	if (c == '\0')
		return (&string[i]);
	if (last_ocurrence != -1)
		return (&string[last_ocurrence]);
	else
		return (NULL);
}
