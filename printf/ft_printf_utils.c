/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:36:57 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/15 16:37:37 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

/*
**	This function receives the list of arguments, the format string and a
**	pointer to the modifiers struct
**	It reads the format string and gets the precision, if the precision
**	is wrong it is set to -1
**	Then returns the format string after the digits
*/

char		*get_precision(va_list args, char *format_string,
t_modifiers *modifiers)
{
	if (*(format_string + 1) == '*')
	{
		modifiers->precision = va_arg(args, int);
		format_string++;
	}
	else if (is_specifier(*(format_string + 1)))
		modifiers->precision = -1;
	else
		modifiers->precision = ft_atoi(format_string + 1);
	while (!is_specifier(*(format_string + 1)))
	{
		format_string++;
	}
	return (format_string);
}

/*
**	This function receives a string and a pointer to the modifiers struct
**	It reads the format string and gets the width specified in it
**	Then returns the format string after the digits
*/

char		*get_width(char *format_string, t_modifiers *modifiers)
{
	modifiers->width = ft_atoi(format_string);
	if (modifiers->width < 0)
	{
		modifiers->width = -modifiers->width;
		modifiers->left_justified = true;
	}
	while (ft_isdigit(*(format_string + 1)))
		format_string++;
	return (format_string);
}

/*
**	This function receives a char and a number
**	It prints the char that number of times
**	Then returns the same number it receives
*/

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
