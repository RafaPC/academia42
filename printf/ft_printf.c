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
	int 	characterSum;

	va_start(args, formatString);
	characterSum = 0;
	while (*formatString)
	{
		if (*formatString == '%')
			formatString = format((char *)++formatString, args, &characterSum);
		else
		{
			write(1, formatString, 1);
			characterSum++;
		}
		formatString++;
	}
	return (characterSum);
}

char *format(char *formatString, va_list args, int *characterSum)
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
	format2(formatString, modifiers, args, characterSum);
	return (formatString);
}

// Buenos dias :D
//PODRÍA CORTAR LA FUNCIÓN POR AQUÍ EN DOS
void	format2(char *formatString, t_modifiers modifiers, va_list args, int *characterSum)
{
	if (*formatString == 'c')
		// Aquí le pasaría el struct como primer argumento
		printChar(va_arg(args, int), characterSum);
	else if (*formatString == 's')
		printString(va_arg(args, char *), modifiers, characterSum);
	else if (*formatString == 'd')
		handleNumber(va_arg(args, int), modifiers, characterSum);
	else if (*formatString == 'x')
		printHex(va_arg(args, unsigned int), characterSum, LOWER_CASE);
	else if (*formatString == 'X')
		printHex(va_arg(args, unsigned int), characterSum, UPPER_CASE);
	else if (*formatString == 'p')
	{
		write(1, "0x", 2);
		(*characterSum) += 2;
		printHex((long int)va_arg(args, void *), characterSum, UPPER_CASE);
	}
}

void printChar(char c, int *characterSum)
{
	write(1, &c, 1);
	(*characterSum)++;
}

void printString(char *string, t_modifiers modifiers, int *characterSum)
{
	int		i;
	int		len;
	char	c;

	len = (modifiers.precision == -1) ? ft_strlen(string) : modifiers.precision;
	i = 0;
	c = (modifiers.zero_padded) ? '0' : ' ';
	if (!modifiers.left_justified && modifiers.width > len)
		print_justification(c, modifiers.width - len);
	while (*string != '\0' && i < len)
	{
		write(1, string++, 1);
		(*characterSum)++;
		i++;
	}
	if (modifiers.left_justified && modifiers.width > len && modifiers.width > modifiers.precision)
		print_justification(c, modifiers.width - modifiers.precision);
	*characterSum += (len > modifiers.width) ? len : modifiers.width;
}
void handleNumber(int n, t_modifiers modifiers, int *characterSum)
{
	int justification_width;

	justification_width = modifiers.width - get_digits(n);
	if (justification_width > 0)
	{
		if (modifiers.width > get_digits(n))
		{
			*characterSum += justification_width;
			if (modifiers.left_justified == FALSE)
				print_justification((modifiers.zero_padded) ? '0' : ' ',
				justification_width);
			printNumber(n, characterSum);
			// Aquí hago que si está justificado a la izquierda imprima espacios, o sea que suda de los ceros
			if (modifiers.left_justified == TRUE)
				print_justification(' ', justification_width);
		}
	}
	else
		printNumber(n, characterSum);
}

void printNumber(int n, int *characterSum)
{
	long int n_copy;
	char c;

	n_copy = n;
	if (n_copy < 0)
	{
		n_copy = -n_copy;
		write(1, "-", 1);
		(*characterSum)++;
	}
	if (n_copy > 9)
	{
		printNumber(n_copy / 10, characterSum);
		c = n_copy % 10 + 48;
	}
	else
		c = n_copy + 48;
	write(1, &c, 1);
	(*characterSum)++;
}

void printHex(long int n, int *characterSum, int letterType)
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
	// 	(*characterSum)++;
	// }
	if (n_copy > 15)
	{
		printHex(n_copy / 16, characterSum, letterType);
		write(1, &hex_characters[n_copy % 16], 1);
	}
	else
		write(1, &hex_characters[n_copy], 1);
	(*characterSum)++;
}
