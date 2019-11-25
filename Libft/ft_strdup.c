/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:51:33 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/25 16:32:04 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *string;
	char *new_string;

	string = (char*)s1;
	if (!(new_string = (char*)malloc((ft_strlen(string) + 1) * sizeof(char))))
		return (NULL);
	else
		return (ft_memcpy(new_string, string, ft_strlen(string) + 1));
}
