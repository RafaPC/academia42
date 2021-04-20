/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:51:33 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/30 21:41:55 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*string;
	char	*new_string;

	string = (char *)s1;
	new_string = (char *)malloc((ft_strlen(string) + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	else
		return (ft_memcpy(new_string, string, ft_strlen(string) + 1));
}
