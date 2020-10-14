/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:52:14 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/14 19:47:24 by rprieto-         ###   ########.fr       */
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

	if (pointer == NULL)
		pointer_length = 3;
	else
		pointer_length = 2 + get_hex_digits((long)pointer);
//Solo para justificación normal
	if (modifiers.width > pointer_length)
	{
		*char_sum += modifiers.width - pointer_length;
		if (modifiers.left_justified)
		{
			print_pointer(pointer, char_sum);
			print_justification(' ', modifiers.width - pointer_length);
		}
		else
		{
			print_justification(' ', modifiers.width - pointer_length);
			print_pointer(pointer, char_sum);
		}
	}
	else
		print_pointer(pointer, char_sum);
}

void	print_pointer(void *pointer, int *char_sum)
{
	*char_sum += write(1, "0x", 2);
	if (pointer == NULL)
		char_sum += write(1, "0", 1);
	else
		print_hex((long)pointer, char_sum, LOWER_CASE);
}
