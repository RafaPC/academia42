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
		else if (ft_atoi(formatString) != -1)
		{
			modifiers.width = ft_atoi(formatString);
			while (ft_isdigit(*(formatString + 1)))
				formatString++;
		}
		else if (*formatString == '*')
			modifiers.width = va_arg(args, int);
		// Cuando se encuentra un punto, si lo siguiente que se encuentra es un asterisco
		// iguala la precision al siguiente argumento, si no, hace un atoi al string de formato
		else if (*(formatString) == '.')
		{
			if (*(formatString + 1) == '*')
			{
				modifiers.precision = va_arg(args, int);
				formatString++;
			}
			else if (is_specifier(*(formatString + 1)))
				modifiers.precision = 0;
			else
				modifiers.precision = (ft_atoi(formatString + 1) == -2) ? 0 : ft_atoi(formatString + 1);
			if (modifiers.precision != -1 && !is_specifier(*formatString))
			{
				while (!is_specifier(*(formatString + 1)))
					formatString++;
			}
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
		printChar(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 's')
		handle_string(va_arg(args, char *), modifiers, char_sum);
	else if (specifier == 'd')
		handle_decimal(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 'i')
		handle_number(va_arg(args, int), modifiers, char_sum);
	else if (specifier == 'x')
		handle_hex_number(va_arg(args, unsigned int), modifiers, char_sum, LOWER_CASE);
	else if (specifier == 'X')
		handle_hex_number(va_arg(args, unsigned int), modifiers, char_sum, UPPER_CASE);
	else if (specifier == 'p')
	{
		handle_pointer(va_arg(args, void *), modifiers, char_sum);
		// (*char_sum) += write(1, "0x", 2);
		// printHex((long int)va_arg(args, void *), char_sum, LOWER_CASE);
	}
	else if (specifier == '%')
	{
		write(1, "%", 1);
		(*char_sum)++;
	}
	else if (specifier == 'u')
	{
		handle_number((unsigned)va_arg(args, long), modifiers, char_sum);
	}
}

void printChar(char c, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.width > 1)
	{
		*char_sum += modifiers.width;
		if (modifiers.left_justified == FALSE)
			print_justification((modifiers.zero_padded) ? '0' : ' ', modifiers.width - 1);
		write(1, &c, 1);
		(*char_sum)++;
		// Aquí hago que si está justificado a la izquierda imprima espacios, o sea que suda de los ceros
		if (modifiers.left_justified == TRUE)
			print_justification((modifiers.zero_padded) ? '0' : ' ', modifiers.width - 1);
	}
	else {
		write(1, &c, 1);
		(*char_sum)++;
	}
}

void printHex(long n, int *char_sum, int letter_type)
{
	long int	n_copy;
	char		*hex_characters;

	hex_characters = (letter_type == LOWER_CASE)
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
		printHex(n_copy / 16, char_sum, letter_type);
		write(1, &hex_characters[n_copy % 16], 1);
	}
	else
		write(1, &hex_characters[n_copy], 1);
	(*char_sum)++;
}
