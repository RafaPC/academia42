/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:10:38 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/13 12:30:58 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst, const void *src, unsigned int len)
{
	int				i;
	unsigned char	*source;
	unsigned char	*destiny;

	i = 0;
	source = (unsigned char*)src;
	destiny = (unsigned char*)dst;
	while (source[i] && i < len)
	{
		destiny[i] = source[i];
		i++;
	}
	return (dst);
}
