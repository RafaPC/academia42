/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:42:43 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/04 16:16:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, unsigned int len)
{
	int	i;
	i = 0;

	while(i < len)
		((char*)b)[i++] = c;
	return (b);
}

int		main(void)
{
	char test[] = "prueba";
	int c = 36;
	ft_memset(test, c, 3);
	printf("%s", test);
	return (0);
}
