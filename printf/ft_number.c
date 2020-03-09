/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:00:42 by rprieto-          #+#    #+#             */
/*   Updated: 2020/03/04 12:07:36 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_number(int n, t_modifiers modifiers, int *char_sum)
{
	int justification_width;

	justification_width = modifiers.width - get_digits(n);
	//TODO: creo que este if se puede quitar
	if (justification_width > 0)
	{
		if (modifiers.width > get_digits(n))
		{
			*char_sum += justification_width;
			if (modifiers.left_justified == FALSE)
				print_justification((modifiers.zero_padded) ? '0' : ' ',
				justification_width);
			print_number(n, char_sum);
			// Aquí hago que si está justificado a la izquierda imprima espacios, o sea que suda de los ceros
			if (modifiers.left_justified == TRUE)
				print_justification(' ', justification_width);
		}
	}
	else
		print_number(n, char_sum);
}

void	print_number(int n, int *char_sum)
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
