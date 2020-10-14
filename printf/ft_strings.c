/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:28:57 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/14 13:15:08 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		handle_string(char *string, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.precision != -1 || string == NULL)
	{
		if (string == NULL)
			string = "(null)";
		print_string(string, modifiers, char_sum);
	}
}

void		print_string(char *string, t_modifiers modifiers, int *char_sum)
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
	if (modifiers.left_justified && modifiers.width > len &&
	modifiers.width > modifiers.precision)
		print_justification(' ', modifiers.width - len);
}

void		print_char(char c, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.width > 1)
	{
		*char_sum += modifiers.width;
		if (modifiers.left_justified == FALSE)
			print_justification((modifiers.zero_padded)
			? '0' : ' ', modifiers.width - 1);
		write(1, &c, 1);
		if (modifiers.left_justified == TRUE)
			print_justification((modifiers.zero_padded)
			? '0' : ' ', modifiers.width - 1);
	}
	else
		*char_sum += write(1, &c, 1);
}

void		print_symbol(t_modifiers modifiers, int *char_sum)
{
	if (modifiers.width > 0)
	{
		*char_sum += modifiers.width;
		if (modifiers.left_justified)
		{
			write(1, "%", 1);
			modifiers.zero_padded = FALSE;
		}
		print_justification((modifiers.zero_padded)
		? '0' : ' ', modifiers.width - 1);
		if (!modifiers.left_justified)
			write(1, "%", 1);
	}
	else
		*char_sum += write(1, "%", 1);
}

unsigned	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}