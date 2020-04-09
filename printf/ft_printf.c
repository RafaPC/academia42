/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:30:22 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/20 11:30:22 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *formatString, ...)
{
	va_list	args;
	int 	char_sum;

	va_start(args, formatString);
	char_sum = 0;
	while (*formatString)
	{
		if (*formatString == '%')
			formatString = format((char *)++formatString, args, &char_sum);
		else
		{
			write(1, formatString, 1);
			char_sum++;
		}
		formatString++;
	}
	return (char_sum);
}

char *format(char *formatString, va_list args, int *char_sum)
{
	t_modifiers modifiers;

	modifiers = ft_initialize_struct();
	// Si entra aquí se ha encontrado '%'
	while (!is_specifier(*formatString))
	{
		if (*formatString == '-')
			modifiers.left_justified = TRUE;
		else if (*formatString == '0')
			modifiers.zero_padded = TRUE;
		else if (ft_atoi(formatString) != 0)
		{
			modifiers.width = ft_atoi(formatString);
			while (ft_isdigit(*(formatString + 1)))
				formatString++;
		}
		else if (*formatString == '*')
			modifiers.width = va_arg(args, int);
		// Cuando se encuentra un punto, si lo siguiente que se encuentra es un asterisco
		// iguala la precision al siguiente argumento, si no, hace un atoi al string de formato
		else if (*(formatString++) == '.')
		{
			if (*formatString == '*')
				modifiers.precision = va_arg(args, int);
			else
				modifiers.precision = (ft_atoi(formatString) < 0) ? 0 : ft_atoi(formatString);
			while (!is_specifier(*(formatString + 1)))
				formatString++;
		}
		formatString++;
	}
	format2(*formatString, modifiers, args, char_sum);
	return (formatString);
}

// Buenos dias :D
//PODRÍA CORTAR LA FUNCIÓN POR AQUÍ EN DOS
void	format2(char specifier, t_modifiers modifiers, va_list args, int *char_sum)
{
	if (specifier == 'c')
		// Aquí le pasaría el struct como primer argumento
		printChar(va_arg(args, int), char_sum);
	else if (specifier == 's')
		handle_string(va_arg(args, char *), modifiers, char_sum);
	else if (specifier == 'd')
		handle_number(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 'x')
		printHex(va_arg(args, unsigned int), char_sum, LOWER_CASE);
	else if (specifier == 'X')
		printHex(va_arg(args, unsigned int), char_sum, UPPER_CASE);
	else if (specifier == 'p')
	{
		write(1, "0x", 2);
		(*char_sum) += 2;
		printHex((long int)va_arg(args, void *), char_sum, UPPER_CASE);
	}
	else if (specifier == '%')
	{
		write(1, "%", 1);
		(*char_sum)++;
	}
}

void printChar(char c, int *char_sum)
{
	write(1, &c, 1);
	(*char_sum)++;
}

void printHex(long int n, int *char_sum, int letterType)
{
	long int	n_copy;
	char		*hex_characters;

	hex_characters = (letterType == LOWER_CASE)
	? "0123456789abcdef" : "0123456789ABCDEF";
	n_copy = n;
	// if (n_copy < 0)
	// {
	// 	n_copy = -n_copy;
	// 	write(1, "-", 1);
	// 	(*char_sum)++;
	// }
	if (n_copy > 15)
	{
		printHex(n_copy / 16, char_sum, letterType);
		write(1, &hex_characters[n_copy % 16], 1);
	}
	else
		write(1, &hex_characters[n_copy], 1);
	(*char_sum)++;
}
