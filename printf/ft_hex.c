/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:52:14 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/20 23:42:05 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	This function receives a long number and does some logic depending
**	on the modifiers
*/

void	handle_hex_number(unsigned int n, t_modifiers modifiers, int *char_sum,
char letter_type)
{
	int justification_width;
	int number_width;
	int	hex_digits;

	hex_digits = get_hex_digits((unsigned long)n);
	number_width = (modifiers.precision != -2 && modifiers.precision >
	hex_digits) ? modifiers.precision : hex_digits;
	justification_width = modifiers.width - number_width;
	if (n == 0 && modifiers.precision == -2)
		justification_width--;
	if (justification_width > 0 && !modifiers.left_justified)
	{
		if (modifiers.zero_padded && modifiers.precision != -2)
			*char_sum += print_justification(' ', justification_width);
		else
			*char_sum += print_justification((modifiers.zero_padded)
			? '0' : ' ', justification_width);
	}
	if (modifiers.precision != -2 && modifiers.precision > hex_digits)
		*char_sum += print_justification('0',
		modifiers.precision - hex_digits);
	if ((n == 0 && modifiers.precision == -2) || n != 0)
		print_hex(n, char_sum, letter_type);
	if (justification_width > 0 && modifiers.left_justified)
		*char_sum += print_justification(' ', justification_width);
}

/*
**	This function receives a long number and prints it in upper or lower case
*/

void	print_hex(unsigned long n, int *char_sum, t_case_type case_type)
{
	char		*hex_characters;

	hex_characters = (case_type == lower_case)
	? "0123456789abcdef" : "0123456789ABCDEF";
	if (n > 15)
	{
		print_hex(n / 16, char_sum, case_type);
		write(1, &hex_characters[n % 16], 1);
	}
	else
		write(1, &hex_characters[n], 1);
	(*char_sum)++;
}

/*
**	This function receives a pointer and does some logic depending
**	on the modifiers
*/

void	handle_pointer(void *pointer, t_modifiers modifiers, int *char_sum)
{
	int pointer_length;
	int justification_width;

	if (modifiers.precision == -1 && pointer == NULL)
		pointer_length = 2;
	else if (pointer == NULL)
		pointer_length = 3;
	else
		pointer_length = 2 + get_hex_digits((unsigned long)pointer);
	if (modifiers.width > pointer_length)
	{
		justification_width = modifiers.width - pointer_length;
		*char_sum += justification_width;
		if (!modifiers.left_justified)
			print_justification(' ', justification_width);
		print_pointer(pointer, modifiers, char_sum);
		if (modifiers.left_justified)
			print_justification(' ', justification_width);
	}
	else
		print_pointer(pointer, modifiers, char_sum);
}

/*
**	This function receives a pointer and it prints some characters depending
**	on the modifiers
*/

void	print_pointer(void *pointer, t_modifiers modifiers, int *char_sum)
{
	int pointer_length;

	pointer_length = get_hex_digits((unsigned long)pointer);
	*char_sum += write(1, "0x", 2);
	if (modifiers.precision != 0)
	{
		if (pointer == NULL && modifiers.precision)
		{
			if (modifiers.precision > 0)
				*char_sum += print_justification('0', modifiers.precision);
			else if (modifiers.precision != -1)
				*char_sum += write(1, "0", 1);
		}
		else if (modifiers.precision)
		{
			if (modifiers.precision > 0 && modifiers.precision > pointer_length)
				*char_sum += print_justification('0',
				modifiers.precision - pointer_length);
			print_hex((unsigned long)pointer, char_sum, lower_case);
		}
	}
}

/*
**	This function receives a long number and return the number of
**	digits it has represented in hexadecimal base
**	including the minus ("-") sign
*/

int		get_hex_digits(unsigned long n)
{
	int	digits;

	digits = 0;
	while (n != 0)
	{
		n /= 16;
		digits++;
	}
	return (digits);
}
