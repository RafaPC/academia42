/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:59:29 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/27 15:36:36 by rprieto-         ###   ########.fr       */
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
