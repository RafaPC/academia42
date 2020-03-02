/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:59:29 by rprieto-          #+#    #+#             */
/*   Updated: 2020/03/02 16:59:47 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
	c == 'u' || c == 'x' || c == 'X' || c == '%') ? TRUE : FALSE;
}

int		ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
	c == '\r' || c == ' ') ? TRUE : FALSE;
}

int		ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	number;
	char		*string;

	i = 0;
	sign = 1;
	number = 0;
	string = (char*)str;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign *= (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number == 0)
			number = str[i] - 48;
		else
			number = number * 10 + str[i] - 48;
		i++;
	}
	return (number * sign);
}

/*
** This function return the number of digits of a given number
*/

unsigned int	get_digits(int n)
{
	unsigned int	digits;

	digits = (n < 0) ? 1 : 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

void	print_justification(char c, int times)
{
	while (times > 0)
	{
		write(1, &c, 1);
		times--;
	}
}

/*
** This function initializes a t_modifier struct with all of its values to zero
*/

t_modifiers	ft_initialize_struct(void)
{
	t_modifiers modifiers;

	modifiers.left_justified = 0;
	modifiers.zero_padded = 0;
	modifiers.precision = -1;
	modifiers.width = -1;
	return (modifiers);
}
