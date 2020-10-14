/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:36:57 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/14 18:54:00 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

char		*get_precision(va_list args, char *format_string,
t_modifiers *modifiers)
{
	if (*(format_string + 1) == '*')
	{
		modifiers->precision = va_arg(args, int);
		format_string++;
	}
	else if (is_specifier(*(format_string + 1)))
		modifiers->precision = 0;
	else
		modifiers->precision = ft_atoi(format_string + 1);
	while (!is_specifier(*(format_string + 1)))
	{
		format_string++;
	}
	return (format_string);
}

char		*get_width(char *format_string, t_modifiers *modifiers)
{
	modifiers->width = ft_atoi(format_string);
	if (modifiers->width < 0)
	{
		modifiers->width = -modifiers->width;
		modifiers->left_justified = TRUE;
	}
	while (*(format_string + 1) >= '0' && *(format_string + 1) <= '9')
		format_string++;
	return (format_string);
}

// int			ft_atoi(const char *str)
// {
// 	int			i;
// 	long int	number;

// 	i = 0;
// 	number = -1;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		if (number == -1)
// 			number = str[i] - 48;
// 		else
// 			number = number * 10 + str[i] - 48;
// 		i++;
// 	}
// 	return (number);
// }

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
