/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:52:14 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/14 21:04:56 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_hex_number(long n, t_modifiers modifiers, int *char_sum,
char letter_type)
{
	int justification_width;
	int number_width;

	number_width = (modifiers.precision != -2 && modifiers.precision >
	get_hex_digits(n)) ? modifiers.precision : get_hex_digits(n);
	justification_width = modifiers.width - number_width;
	if (n == 0 && modifiers.precision == -2)
		justification_width--;
	if (n == 0 && modifiers.precision != -2)
		modifiers.precision--;
	if (justification_width > 0 && modifiers.left_justified == FALSE)
	{
		if (modifiers.zero_padded && modifiers.precision != -2 &&
		modifiers.width != -1)
			*char_sum += print_justification(' ', justification_width);
		else
			*char_sum += print_justification((modifiers.zero_padded)
			? '0' : ' ', justification_width);
	}
	if (modifiers.precision != -2)
		*char_sum += print_justification('0', modifiers.precision - get_hex_digits(n));
	if (n != 0 || (modifiers.precision != 0 && modifiers.precision != -1))
		print_hex(n, char_sum, letter_type);
	if (justification_width > 0 && modifiers.left_justified)
		*char_sum += print_justification(' ', justification_width);
}

void	print_hex(long n, int *char_sum, char letter_type)
{
	char		*hex_characters;

	hex_characters = (letter_type == LOWER_CASE)
	? "0123456789abcdef" : "0123456789ABCDEF";
	if (n > 15)
	{
		print_hex(n / 16, char_sum, letter_type);
		write(1, &hex_characters[n % 16], 1);
	}
	else
		write(1, &hex_characters[n], 1);
	(*char_sum)++;
}

int		get_hex_digits(long n)
{
	unsigned int	digits;

	digits = (n < 0) ? 1 : 0;
	while (n != 0)
	{
		n /= 16;
		digits++;
	}
	return (digits);
}

void	handle_pointer(void *pointer, t_modifiers modifiers, int *char_sum)
{
	int pointer_length;
	int justification_width;

	if (modifiers.precision == -1)
		pointer_length = 2;
	else if (pointer == NULL)
		pointer_length = 3;
	else
		pointer_length = 2 + get_hex_digits((long)pointer);
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

void	print_pointer(void *pointer, t_modifiers modifiers, int *char_sum)
{
	int pointer_length;

	pointer_length = get_hex_digits((long)pointer);
	*char_sum += write(1, "0x", 2);
	if (pointer == NULL)
	{
		if (modifiers.precision > 0)
			*char_sum += print_justification('0', modifiers.precision);
		else if (modifiers.precision != -1)
			*char_sum += write(1, "0", 1);
	}
	else
	{
		if (modifiers.precision > 0 && modifiers.precision > pointer_length)
			*char_sum += print_justification('0',
			modifiers.precision - pointer_length);
		print_hex((long)pointer, char_sum, LOWER_CASE);
	}
}
