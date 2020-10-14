/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:36:57 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/14 13:31:38 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_justification(char c, int times)
{
	int times_copy;

	times_copy = times;
	while (times > 0)
	{
		write(1, &c, 1);
		times--;
	}
	return (times_copy);
}

unsigned	get_digits(int n)
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

int			abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}
