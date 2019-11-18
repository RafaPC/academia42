/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:13:05 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/15 12:39:33 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	int				i;

	i = 0;
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (i < n && (unsigned char)c != source[i - 1])
	{
		dest[i] = source[i];
		i++;
	}
	if (i < n)
		return (&dst[i]);
	else
		return (dst);
}
