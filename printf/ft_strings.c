/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:28:57 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/20 15:23:12 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

/*
**	This function receives a string and does some logic depending
**	on the modifiers
**	If the precision is set well or is not set, then calls print_string()
*/

void	handle_string(char *string, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.precision != -1)
	{
		if (string == NULL)
			string = "(null)";
		print_string(string, modifiers, char_sum);
	}
	else if (modifiers.width > 0)
		*char_sum += print_justification(' ', modifiers.width);
}

/*
**	This function prints a string received according to the modifiers
*/

void	print_string(char *string, t_modifiers modifiers, int *char_sum)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	if (modifiers.precision >= 0)
		len = ((int)ft_strlen(string) < modifiers.precision)
		? (int)ft_strlen(string) : modifiers.precision;
	else
		len = (int)ft_strlen(string);
	c = (modifiers.zero_padded) ? '0' : ' ';
	*(char_sum) += (modifiers.width > len) ? modifiers.width : len;
	if (!modifiers.left_justified && modifiers.width > len)
		print_justification(c, modifiers.width - len);
	while (*string != '\0' && i < len)
	{
		write(1, string++, 1);
		i++;
	}
	if (modifiers.left_justified && modifiers.width > len)
		print_justification(' ', modifiers.width - len);
}

/*
**	This function receives a char and prints it according to the modifiers
*/

void	print_char(char c, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.width > 1)
	{
		*char_sum += modifiers.width;
		if (!modifiers.left_justified)
			print_justification((modifiers.zero_padded)
			? '0' : ' ', modifiers.width - 1);
		write(1, &c, 1);
		if (modifiers.left_justified)
			print_justification((modifiers.zero_padded)
			? '0' : ' ', modifiers.width - 1);
	}
	else
		*char_sum += write(1, &c, 1);
}

/*
**	This function prints the symbol % according to the modifiers
*/

void	print_symbol(t_modifiers modifiers, int *char_sum)
{
	if (modifiers.width > 1)
	{
		*char_sum += modifiers.width;
		if (modifiers.left_justified)
		{
			write(1, "%", 1);
			modifiers.zero_padded = false;
		}
		print_justification((modifiers.zero_padded)
		? '0' : ' ', modifiers.width - 1);
		if (!modifiers.left_justified)
			write(1, "%", 1);
	}
	else
		*char_sum += write(1, "%", 1);
}
