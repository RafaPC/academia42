/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:58:54 by rprieto-          #+#    #+#             */
/*   Updated: 2020/09/14 16:52:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_string(char *string, t_modifiers modifiers, int *char_sum)
{
	char print;

	print = TRUE;
	if (modifiers.precision == -1)
		print = FALSE;
	if (modifiers.width < 0)
	{
		modifiers.left_justified = TRUE;
		modifiers.width = -modifiers.width;
	}
	if (string == NULL)
	{
		string = "(null)";
		if (modifiers.precision > 0 && modifiers.precision < 6)
			modifiers.precision = 0;
	}
	if (print)
		print_string(string, modifiers, char_sum);
}

void	print_string(char *string, t_modifiers modifiers, int *char_sum)
{
	int		i;
	int		len;
	char	c;
	//FIXME: Esto puede que sobre
	if (modifiers.width < 0)
		modifiers.left_justified = TRUE;
	i = 0;
	//podría ser que hubieran puesto la precisión con el asterisco a -1
	//TODO: a lo mejor debería de checkear si es negativo
	//FIXME: Cambiar el ultimo operando a -1
	len = (ft_strlen(string) < modifiers.precision) ? ft_strlen(string) : modifiers.precision;
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
