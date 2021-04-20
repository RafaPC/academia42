/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:01:23 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/31 09:48:01 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_printf(int fd, const char *format_string, ...)
{
	va_list		args;
	int			char_sum;
	t_modifiers	modifiers;

	va_start(args, format_string);
	char_sum = 0;
	while (*format_string)
	{
		if (*format_string == '%')
		{
			modifiers = ft_initialize_struct(fd);
			format_string = read_modifiers(args,
					(char *)++format_string, &modifiers);
			format(args, *format_string, modifiers, &char_sum);
		}
		else
			char_sum += write(fd, format_string, 1);
		if (*format_string)
			format_string++;
	}
	va_end(args);
	return (char_sum);
}

/*
**	This function reads the format string searching for modifiers and
**	setting the values in the modifiers struct
**	Then returns the format string when it encounters a specifier
*/

char	*read_modifiers(va_list args, char *format_string,
t_modifiers *modifiers)
{
	while (is_flag(*format_string))
	{
		if (*format_string == '-')
			modifiers->left_justified = true;
		else if (*format_string == '0')
			modifiers->zero_padded = true;
		else if (*(format_string) == '.')
			format_string = get_precision(args, format_string, modifiers);
		else if (*format_string == '*')
		{
			modifiers->width = va_arg(args, int);
			if (modifiers->width < 0)
			{
				modifiers->width = -modifiers->width;
				modifiers->left_justified = true;
			}
		}
		else if (ft_isdigit(*format_string))
			format_string = get_width(format_string, modifiers);
		format_string++;
	}
	return (format_string);
}

/*
**	This function reads the specifier it gets as a parameter and calls
**	the correct function depending on the type of specifier
*/

void	format(va_list args, char specifier, t_modifiers modifiers,
int *char_sum)
{
	if (specifier == 'i')
		handle_number(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 'd')
		handle_number(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 'u')
		handle_number(va_arg(args, unsigned int), modifiers, char_sum);
	else if (specifier == 'x')
		handle_hex_number(va_arg(args, unsigned int), modifiers, char_sum,
			lower_case);
	else if (specifier == 'X')
		handle_hex_number(va_arg(args, unsigned int), modifiers, char_sum,
			upper_case);
	else if (specifier == 'p')
		handle_pointer(va_arg(args, void *), modifiers, char_sum);
	else if (specifier == 'c')
		print_char(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 's')
		handle_string(va_arg(args, char *), modifiers, char_sum);
	else if (specifier == '%')
		print_symbol(modifiers, char_sum);
}

/*
**	This function initialices modifiers values and returns them in a struct
*/

t_modifiers	ft_initialize_struct(int fd)
{
	t_modifiers	modifiers;

	modifiers.left_justified = false;
	modifiers.zero_padded = false;
	modifiers.precision = -2;
	modifiers.width = 0;
	modifiers.fd = fd;
	return (modifiers);
}

/*
**	This functions recieves a char and returns true or false
**	wether it's a flag or not
*/

t_bool	is_flag(char c)
{
	if (c == '-' || ft_isdigit(c) || c == '.' || c == '*')
		return (true);
	return (false);
}
