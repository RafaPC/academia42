/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:19:06 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/27 16:38:13 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	real_len;
	char			*string;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	real_len = ft_strlen(&s[start]);
	real_len = (real_len < len) ? real_len : len;
	if (start >= (unsigned int)ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (!(string = (char*)malloc((real_len + 1) * sizeof(char))))
		return (NULL);
	while (j < real_len)
		string[j++] = s[i++];
	string[j] = '\0';
	return (string);
}
