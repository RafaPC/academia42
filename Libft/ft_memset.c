/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:18:10 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/13 09:10:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *b, int c, unsigned int len)
{
	unsigned char *pointer;

	pointer = (unsigned char)b;
	while (len-- > 0)
		*(pointer++) = (unsigned char)c;
	return (b);
}
