/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:19:06 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/19 18:17:32 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	real_len;
	char			*string;

	i = start;
	j = 0;
	real_len = ft_strlen(&s[start]);
	real_len = (real_len < len) ? real_len : len;
	string = (char*)malloc((real_len + 1) * sizeof(char));
	while (j < real_len)
		string[j++] = s[i++];
	string[j] = '\0';
	return (string);  
}
