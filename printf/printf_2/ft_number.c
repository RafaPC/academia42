/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:48:55 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/12 15:56:29 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void	handle_number(long int n, t_modifiers modifiers, int *char_sum)
{
	int justification_width;

	if (modifiers.width < 0)
	{
		modifiers.width = -modifiers.width;
		modifiers.left_justified = TRUE;
		if (n < 0)
			modifiers.width++;
	}
	if (!(n == 0 && (modifiers.precision == 0 || modifiers.precision == -1)))
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
			if (justification_width > 0)
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

void	print_number2(long int n, t_modifiers modifiers, int *char_sum)
{
	int number_width;

	number_width = (modifiers.precision > (int)get_digits(ABS(n))) 
	? modifiers.precision : (int)get_digits(ABS(n));
	if (n < 0)
		number_width++;
	if (!modifiers.left_justified)
		print_justification(' ', modifiers.width - number_width);
	if (n < 0)
	{
		*char_sum += write(1, "-", 1);
		number_width--;
	}
	if (modifiers.precision > (int)get_digits(ABS(n)))
		print_justification('0', modifiers.precision - get_digits(ABS(n)));
	print_number(ABS(n), char_sum);
	if (modifiers.left_justified){
		if (n < 0)
			number_width++;
		print_justification(' ', modifiers.width - number_width);
	}
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

// void	handle_integer(int n, t_modifiers modifiers, int *char_sum)
// {
// 	int		digits;
// 	char	*number_string;
// 	// char            *aux;

// 	modifiers.width = modifiers.width;
// 	digits = (int)get_digits(n);
// 	if (digits > modifiers.precision)
// 		modifiers.precision = -2;
// 	if (n < 0 && (modifiers.precision > 0 || (modifiers.width > 0 && modifiers.zero_padded)))
// 	{
// 		*char_sum += write(1, "-", 1);
// 		n = -n;
// 		modifiers.width--;
// 	}
// 	else if(!modifiers.zero_padded && (modifiers.width > modifiers.precision || modifiers.width > (int)get_digits(n)))
// 	{
// 		*char_sum += ft_printf("%*s", modifiers.width - 
// 		get_greater(modifiers.precision, get_digits(n)), "");
// 		modifiers.width = 0;
// 	}

// 	if (modifiers.precision > 0)
// 	{
// 		if (modifiers.precision > digits)
// 		{
// 			modifiers.zero_padded = TRUE;
// 			modifiers.width = modifiers.precision;    
// 		}
// 	}
// 	number_string = ft_itoa(n);
// }

// char    *handle_integer(int n, t_modifiers *modifiers, int *char_sum)
// {
// 	// int digits;

// 	// digits = get_digits(ABS(n));
// 	if (modifiers->width <= (int)get_digits(n) || modifiers->width <= modifiers->precision)
// 		modifiers->width = -1;
// 	if (modifiers->width > modifiers->precision && modifiers->precision > (int)get_digits(n))
// 	{
// 		print_justification(' ', modifiers->width - modifiers->precision);
// 		if (n < 0)
// 			*char_sum += write(1, "-", 1);
// 		print_justification('0', modifiers->precision - get_digits(ABS(n)));
// 		ft_putnbr_fd(ABS(n), 1);
// 	}
// 	return (NULL);
// }

// char	*justification_string(int number_digits, int spaces, int zeros)
// {
// 	char	aux[zeros + 1];
// 	char	*number;


// 	if (spaces)
// 	{
// 		number = malloc(spaces * sizeof(char));
// 		ft_memset(number, ' ', spaces);
// 		if (zeros)
// 			number = ft_strjoin_and_free(number, ft_memset(aux, '0', zeros));
// 	}
// 	else
// 	{
// 		number = malloc(zeros * sizeof(char));
// 		ft_memset(number, '0', spaces);
// 	}
// 	return (number);
// }
