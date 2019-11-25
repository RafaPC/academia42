/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:24:49 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/25 15:38:41 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fill_nbr(char *string, unsigned int index, int number)
{
	if (number > 9)
	{
		fill_nbr(string, index - 1, number / 10);
		string[index] = (number % 10) + 48;
	}
	else
		string[index] = number + 48;
}

unsigned int	get_digits(int n)
{
	unsigned int	digits;

	digits = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char			*ft_itoa(int n)
{
	char			*string;
	int				n_copy;
	unsigned int	digits;
	unsigned int	index;

	if (n == 0)
		return (ft_strdup("0"));
	digits = get_digits(n);
	n_copy = n;
	index = digits - 1;
	if (!(string = (char*)malloc((digits + 1) * sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		n = -n;
	}
	fill_nbr(string, index, n);
	string[digits] = '\0';
	return (string);
}
