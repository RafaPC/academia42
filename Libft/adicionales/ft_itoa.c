/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:24:49 by rprieto-          #+#    #+#             */
/*   Updated: 2019/11/20 18:12:40 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	labuena(char *string, unsigned int index, int number)
{
	if (number > 9)
	{
		labuena(string, index - 1, number / 10);
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
	{
		string = (char*)malloc(2);
		string[0] = '0';
		string[1] = '\0';
		return (string);
	}
	digits = get_digits(n);
	n_copy = n;
	index = digits - 1;
	string = (char*)malloc((digits + 1) * sizeof(char));
	if (n < 0)
	{
		string[0] = '-';
		n = -n;
	}
	labuena(string, index, n);
	string[digits] = '\0';
	return (string);
}

int	main(int argc, char const *argv[])
{
	printf("%s", ft_itoa(-28947));
	return 0;
}
