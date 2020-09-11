/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:59:29 by rprieto-          #+#    #+#             */
/*   Updated: 2020/09/11 13:46:02 by rprieto-         ###   ########.fr       */
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
	number = -1;
	string = (char*)str;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number == -1)
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

/*
** This function return the number of digits of an hexadecimal given number
*/

unsigned int	get_hex_digits(int n)
{
	unsigned int	digits;

	digits = (n < 0) ? 1 : 0;
	while (n != 0)
	{
		n /= 16;
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

	modifiers.left_justified = FALSE;
	modifiers.zero_padded = FALSE;
	modifiers.precision = -2;
	modifiers.width = 0;
	return (modifiers);
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9') ? TRUE : FALSE;
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
