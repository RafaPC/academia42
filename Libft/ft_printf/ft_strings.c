/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:28:57 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/31 09:48:08 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

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
		*char_sum += print_justification(modifiers.fd, ' ', modifiers.width);
}

/*
**	This function prints a string received according to the modifiers
*/

/*
** TODO: DOUBLE check the i++ thing
*/

void	print_string(char *string, t_modifiers modifiers, int *char_sum)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	if (modifiers.precision >= 0
		&& (int)ft_strlen(string) < modifiers.precision)
		len = modifiers.precision;
	else
		len = (int)ft_strlen(string);
	c = ' ';
	if (modifiers.zero_padded)
		c = '0';
	if (modifiers.width > len)
		*(char_sum) += modifiers.width;
	else
		*(char_sum) += len;
	if (!modifiers.left_justified && modifiers.width > len)
		print_justification(modifiers.fd, c, modifiers.width - len);
	while (*string != '\0' && i++ < len)
		write(modifiers.fd, string++, 1);
	if (modifiers.left_justified && modifiers.width > len)
		print_justification(modifiers.fd, ' ', modifiers.width - len);
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
		{
			if (modifiers.zero_padded)
				print_justification(modifiers.fd, '0', modifiers.width - 1);
			else
				print_justification(modifiers.fd, ' ', modifiers.width - 1);
		}
		write(modifiers.fd, &c, 1);
		if (modifiers.left_justified)
		{
			if (modifiers.zero_padded)
				print_justification(modifiers.fd, '0', modifiers.width - 1);
			else
				print_justification(modifiers.fd, ' ', modifiers.width - 1);
		}
	}
	else
		*char_sum += write(modifiers.fd, &c, 1);
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
			write(modifiers.fd, "%", 1);
			modifiers.zero_padded = false;
		}
		if (modifiers.zero_padded)
			print_justification(modifiers.fd, '0', modifiers.width - 1);
		else
			print_justification(modifiers.fd, '0', modifiers.width - 1);
		if (!modifiers.left_justified)
			write(modifiers.fd, "%", 1);
	}
	else
		*char_sum += write(modifiers.fd, "%", 1);
}
