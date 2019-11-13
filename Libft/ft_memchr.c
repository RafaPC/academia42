/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:03:55 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/13 12:31:14 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	int		i;
	char	*string;

	i = 0;
	string = (char *)s;
	while (string[i])
	{
		if (string[i] == (unsigned char)c)
			return (&string[i]);
		i++;
	}
	return (0);
}
