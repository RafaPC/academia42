/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:58:54 by rprieto-          #+#    #+#             */
/*   Updated: 2020/03/04 12:53:23 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_string(char *string, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.width < 0)
	{
		modifiers.left_justified = TRUE;
		modifiers.width = -modifiers.width;
	}
	print_string(string, modifiers, char_sum);
}

void	print_string(char *string, t_modifiers modifiers, int *char_sum)
{
	int		i;
	int		len;
	char	c;

	if (modifiers.width < 0)
		modifiers.left_justified = TRUE;

	i = 0;
	//WARNING: podría ser que hubieran puesto la precisión con el asterisco a -1
	len = (modifiers.precision == -1) ? ft_strlen(string) : modifiers.precision;
	c = (modifiers.zero_padded) ? '0' : ' ';
	if (!modifiers.left_justified && modifiers.width > len)
		print_justification(c, modifiers.width - len);
	while (*string != '\0' && i < len)
	{
		write(1, string++, 1);
		(*char_sum)++;
		i++;
	}
	if (modifiers.left_justified && modifiers.width > len &&
	modifiers.width > modifiers.precision)
		print_justification(' ', modifiers.width - len);
	*char_sum += modifiers.width - len;
}
