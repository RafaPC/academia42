/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:48:55 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/14 01:00:38 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void	handle_number(long int n, t_modifiers modifiers, int *char_sum)
{
	if (!(n == 0 && (modifiers.precision == 0 || modifiers.precision == -1)))
	{
		if (modifiers.precision != -2 && modifiers.width)
			handle_number2(n, modifiers, char_sum);
		else
		{
			if (modifiers.zero_padded && n < 0 && !modifiers.left_justified)
				modifiers.width--;
			if (n < 0 && ((modifiers.zero_padded && modifiers.width) ||
			(modifiers.precision != -2)) && !modifiers.left_justified)
			{
				*char_sum += write(1, "-", 1);
				n = -n;
			}
			if (modifiers.precision != -2 && modifiers.width == 0)
			{
				modifiers.width = modifiers.precision;
				modifiers.zero_padded = TRUE;
			}
			handle_number1_5(n, modifiers, char_sum);
		}
	}
	else
		*char_sum += ft_printf("%*s", modifiers.width, "");
}

void	handle_number1_5(long int n, t_modifiers modifiers, int *char_sum)
{
	int justification_width;

	justification_width = modifiers.width - get_digits(n);
	if (justification_width > 0)
	{
		*char_sum += justification_width;
		if (modifiers.left_justified == FALSE)
			print_justification((modifiers.zero_padded) ? '0' : ' ',
			justification_width);
		print_number(n, char_sum);
		if (modifiers.left_justified == TRUE)
			print_justification(' ', justification_width);
	}
	else
		print_number(n, char_sum);
}

void	handle_number2(long int n, t_modifiers modifiers, int *char_sum)
{
	int number_width;
	int digits;

	digits = (int)get_digits(ABS(n));
	number_width = modifiers.precision > digits ? modifiers.precision : digits;
	if (n < 0)
		number_width++;
	if (!modifiers.left_justified)
		*char_sum += print_justification(' ', modifiers.width - number_width);
	if (n < 0)
		*char_sum += write(1, "-", 1);
	if (modifiers.precision > digits)
		*char_sum += print_justification('0', modifiers.precision - digits);
	print_number(ABS(n), char_sum);
	if (modifiers.left_justified)
		*char_sum += print_justification(' ', modifiers.width - number_width);
}

void	handle_decimal(long n, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.precision != 0 && modifiers.precision != -1)
	{
		if (modifiers.precision != -2)
		{
			if (modifiers.width == 0)
			{
				modifiers.zero_padded = TRUE;
				modifiers.width = modifiers.precision;
				modifiers.precision = -2;
				if (n < 0)
					modifiers.width++;
			}
		}
		handle_number(n, modifiers, char_sum);
	}
	else if (modifiers.width != 0 && modifiers.precision == 0)
		*char_sum += ft_printf("%*s", modifiers.width, "");
	else if (modifiers.precision == -1)
		*char_sum += ft_printf("%i", n);
}

void	print_number(long n, int *char_sum)
{
	long int	n_copy;
	char		c;

	n_copy = n;
	if (n_copy < 0)
	{
		n_copy = -n_copy;
		write(1, "-", 1);
		(*char_sum)++;
	}
	if (n_copy > 9)
	{
		print_number(n_copy / 10, char_sum);
		c = n_copy % 10 + 48;
	}
	else
		c = n_copy + 48;
	write(1, &c, 1);
	(*char_sum)++;
}
