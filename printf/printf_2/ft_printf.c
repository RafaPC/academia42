/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:01:23 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/06 20:54:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format_string, ...)
{
	va_list	args;
	int		char_sum;

	va_start(args, format_string);
	char_sum = 0;
	while (*format_string)
	{
		if (*format_string == '%')
			format_string = format((char *)++format_string, args, &char_sum);
		else
			char_sum += write(1, format_string, 1);
		format_string++;
	}
	return (char_sum);
}

char	*format(char *format_string, va_list args, int *char_sum)
{
	t_modifiers modifiers;

	modifiers = ft_initialize_struct();
	while (!is_specifier(*format_string))
	{
		if (*format_string == '-')
			modifiers.left_justified = TRUE;
		else if (*format_string == '0')
			modifiers.zero_padded = TRUE;
		else if (*(format_string) == '.')
			get_precision(args, &format_string, &modifiers);
		else if (*(format_string) == ' ')
			*char_sum += write(1, " ", 1);
		else if (*format_string == '*')
			modifiers.width = va_arg(args, int);
		else
		{
			modifiers.width = ft_atoi(format_string);
			while (ft_isdigit(*(format_string + 1)))
				format_string++;
		}
		format_string++;
	}
	return (format_string);
}
