/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:48:55 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/19 16:42:23 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

/*
**	It receives a number and does some logic depending on the modifiers
*/

void	handle_number(long n, t_modifiers modifiers, int *char_sum)
{
	if (n == 0 && (modifiers.precision == 0 || modifiers.precision == -1))
		*char_sum += ft_printf("%*s", modifiers.width, "");
	else if (modifiers.precision != -2 && modifiers.width)
		handle_number_prec_width(n, modifiers, char_sum);
	else
	{
		if (n < 0 && modifiers.zero_padded && !modifiers.left_justified &&
		modifiers.width)
			modifiers.width--;
		else if (modifiers.precision != -2 && modifiers.width == 0)
		{
			modifiers.width = modifiers.precision;
			modifiers.zero_padded = true;
			modifiers.left_justified = false;
		}
		if (n < 0 && ((modifiers.zero_padded && modifiers.width) ||
		(modifiers.precision != -2)) && !modifiers.left_justified)
		{
			*char_sum += write(1, "-", 1);
			n = -n;
		}
		handle_number_no_prec(n, modifiers, char_sum);
	}
}

/*
**	This function receives a number without the precision set and prints
**	some justification depending on the width
**	Then prints the number
*/

void	handle_number_no_prec(long n, t_modifiers modifiers, int *char_sum)
{
	int justification_width;

	justification_width = modifiers.width - ft_nbrlen(n) - ((n < 0) ? 1 : 0);
	if (justification_width > 0)
	{
		*char_sum += justification_width;
		if (!modifiers.left_justified)
			print_justification((modifiers.zero_padded) ? '0' : ' ',
			justification_width);
		print_number(n, char_sum);
		if (modifiers.left_justified)
			print_justification(' ', justification_width);
	}
	else
		print_number(n, char_sum);
}

/*
**	This function receives a number with precision and width
**	and prints some justification depending on them
**	Then prints the number
*/

void	handle_number_prec_width(long n, t_modifiers modifiers,
int *char_sum)
{
	int number_width;
	int digits;
	int justification_width;

	digits = ft_nbrlen(ft_abs(n));
	number_width = modifiers.precision > digits ? modifiers.precision : digits;
	if (n < 0)
		number_width++;
	justification_width = modifiers.width - number_width;
	if (!modifiers.left_justified && justification_width > 0)
		*char_sum += print_justification(' ', justification_width);
	if (n < 0)
		*char_sum += write(1, "-", 1);
	if (modifiers.precision > digits)
		*char_sum += print_justification('0', modifiers.precision - digits);
	print_number(ft_abs(n), char_sum);
	if (modifiers.left_justified && justification_width > 0)
		*char_sum += print_justification(' ', justification_width);
}

/*
**	This function receives a long number and a pointer to the character counter
**	It prints the number and sums char_sum by 1 for each character it prints
*/

void	print_number(long n, int *char_sum)
{
	long int	n_copy;
	char		c;

	n_copy = n;
	if (n_copy < 0)
	{
		n_copy = -n_copy;
		*char_sum += write(1, "-", 1);
	}
	if (n_copy > 9)
	{
		print_number(n_copy / 10, char_sum);
		c = n_copy % 10 + 48;
	}
	else
		c = n_copy + 48;
	*char_sum += write(1, &c, 1);
}
