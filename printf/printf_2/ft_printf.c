/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:01:23 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/13 13:00:29 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int		ft_printf(const char *format_string, ...)
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
			modifiers = ft_initialize_struct();
			format_string = read_modifiers(args,
			(char *)++format_string, &modifiers, &char_sum);
			format2(args, *format_string, modifiers, &char_sum);
		}
		else
			char_sum += write(1, format_string, 1);
		format_string++;
	}
	return (char_sum);
}

/*TODO: aqui al final o algo hacer que imprima los caracteres escapados */
char	*read_modifiers(va_list args, char *format_string,
t_modifiers *modifiers, int *char_sum)
{
	while (!is_specifier(*format_string))
	{
		if (*format_string == '-')
			modifiers->left_justified = TRUE;
		else if (*format_string == '0')
			modifiers->zero_padded = TRUE;
		else if (*(format_string) == '.')
			format_string = get_precision(args, format_string, modifiers);
		else if (*(format_string) == ' ')
			*char_sum += write(1, " ", 1);
		else if (*format_string == '*')
		{
			modifiers->width = va_arg(args, int);
			if (modifiers->width < 0)
			{
				modifiers->width = -modifiers->width;
				modifiers->left_justified = TRUE;
			}
		}
		else
			format_string = get_width(format_string, modifiers);
		format_string++;
	}
	return (format_string);
}

void	format2(va_list args, char specifier, t_modifiers modifiers,
int *char_sum)
{
	if (specifier == 'i')
		handle_number(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 'x')
		handle_hex_number(va_arg(args, long), modifiers, char_sum, LOWER_CASE);
	else if (specifier == 'X')
		handle_hex_number(va_arg(args, long), modifiers, char_sum, UPPER_CASE);
	else if (specifier == 'p')
		handle_pointer(va_arg(args, void *), modifiers, char_sum);
	else if (specifier == 'c')
		print_char(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 's')
		handle_string(va_arg(args, char*), modifiers, char_sum);
	else
		print_symbol(modifiers, char_sum);
}
