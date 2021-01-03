/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:55:10 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/26 18:04:51 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (!s1) ? (char*)s2 : (char*)s1;
	if (!(joined_str = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
	* sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined_str[j++] = s2[i++];
	joined_str[j] = '\0';
	return (joined_str);
}
