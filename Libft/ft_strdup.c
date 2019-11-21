/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:51:33 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/21 16:27:12 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *string;
	char *new_string;

	string = (char*)s1;
	new_string = (char*)malloc((strlen(string) + 1) + sizeof(char));
	if (!new_string)
		return (NULL);
	else
		return (ft_memcpy(new_string, string, ft_strlen(string) + 1));
}
