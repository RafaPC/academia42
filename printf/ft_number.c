/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:00:42 by rprieto-          #+#    #+#             */
/*   Updated: 2020/09/22 17:49:07 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_number(int n, t_modifiers modifiers, int *char_sum)
{
	int justification_width;
	if (!(n == 0 && modifiers.precision == 0 || modifiers.precision == -1))
	{
		if (modifiers.precision!= -2 && modifiers.width)
			print_number2(n, modifiers, char_sum);
		else
		{
			if (modifiers.zero_padded && modifiers.width != 0 && n < 0)
				modifiers.width--;
			//Rellena con zeros si bien tiene el zero padded puesto o si tiene puesta la precision
			if (n < 0 && ((modifiers.zero_padded && modifiers.width) || (modifiers.precision != -2)) && modifiers.left_justified == FALSE)
			{
				write(1, "-", 1);
				(*char_sum)++;
				n = -n;
				// if (modifiers.width != 0)
				// 	justification_width--;
			}
			if (modifiers.precision != -2 && modifiers.width == 0)
			{
				modifiers.width = modifiers.precision;
				modifiers.zero_padded = TRUE;
			}
			justification_width = modifiers.width - get_digits(n);
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
			else
				print_number(n, char_sum);
		}
	}
	else
		*char_sum += ft_printf("%*s", modifiers.width, "");
}

void	print_number2(int n, t_modifiers modifiers, int *char_sum)
{
	int justification_width;
	int number_width;

	number_width = (modifiers.precision > get_digits(ABS(n))) 
	? modifiers.precision : get_digits(ABS(n));
	if (n < 0)
		number_width++;
	if (!modifiers.left_justified)
		print_justification(' ', modifiers.width - number_width);
	if (n < 0)
	{
		*char_sum += write(1, "-", 1);
		number_width--;
	}
	if (modifiers.precision > get_digits(ABS(n)))
		print_justification('0', modifiers.precision - get_digits(ABS(n)));
	print_number(ABS(n), char_sum);
	if (modifiers.left_justified){
		if (n < 0)
			number_width++;
		print_justification(' ', modifiers.width - number_width);
	}
}

void	handle_decimal(int n, t_modifiers modifiers, int *char_sum)
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
		// else if (modifiers.width != 0)
		// {
			
		// }
		handle_number(n ,modifiers, char_sum);
	}
	else if(modifiers.width != 0 && modifiers.precision == 0)
	{
		*char_sum += ft_printf("%*s", modifiers.width, "");
	}
	else if(modifiers.precision == -1)
	{
		*char_sum += ft_printf("%i", n);
	}
}

void	handle_hex_number(long n, t_modifiers modifiers, int *char_sum, int letter_type)
{
	int justification_width;

	justification_width = modifiers.width - get_hex_digits(n);
	//TODO: creo que este if se puede quitar
	if (modifiers.width > get_hex_digits(n))
	{
		*char_sum += justification_width;
		if (modifiers.left_justified == FALSE)
			print_justification((modifiers.zero_padded) ? '0' : ' ',
			justification_width);
		printHex(n, char_sum, letter_type);
		// Aquí hago que si está justificado a la izquierda imprima espacios, o sea que suda de los ceros
		if (modifiers.left_justified == TRUE)
			print_justification(' ', justification_width);
	}
	else
		printHex(n, char_sum, letter_type);
}

void	handle_pointer(void *pointer, t_modifiers modifiers, int *char_sum)
{
	int pointer_length;

	if (pointer == NULL)
		pointer_length = 5;
	else
		pointer_length = 2 + get_hex_digits((long)pointer);
	// Solo para justificación normal
	if (modifiers.width > pointer_length)
	{
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
	if (pointer == NULL)
		char_sum += write(1, "(nil)", 5);
	else
	{
		char_sum += write(1, "0x", 2);
		printHex((long)pointer, char_sum, LOWER_CASE);
	}
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
