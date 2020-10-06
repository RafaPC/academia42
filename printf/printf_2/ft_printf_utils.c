/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:36:57 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/06 21:01:40 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
t_modifiers ft_initialize_struct(void)
{
	t_modifiers modifiers;

	modifiers.left_justified = FALSE;
	modifiers.zero_padded = FALSE;
	modifiers.precision = -2;
	modifiers.width = 0;
	return (modifiers);
}

int		    is_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
	c == 'u' || c == 'x' || c == 'X' || c == '%') ? TRUE : FALSE;
}

void        get_precision(va_list args, char **format_string, t_modifiers *modifiers)
{
    if (*(*(format_string) + 1) == '*')
    {
        modifiers->precision = va_arg(args, int);
        (*format_string)++;
    }
    else if (is_specifier(*(*(format_string) + 1)))
        modifiers->precision = 0;
    else
    // TODO: aqui antes estaba esto pero no tenía sentido porque el atoi no puede devolver -2, solo -1
    //modifiers->precision = (ft_atoi(format_string + 1) == -2)
        //? 0 : ft_atoi(format_string);
        modifiers->precision = ft_atoi(*format_string + 1);
    while (!is_specifier(*(*(format_string) + 1)))
        (*format_string)++;
}

int		ft_atoi(const char *str)
{
	int			i;
	long int	number;
	char		*string;

	i = 0;
	number = -1;
	string = (char*)str;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number == -1)
			number = str[i] - 48;
		else
			number = number * 10 + str[i] - 48;
		i++;
	}
	return (number);
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9') ? TRUE : FALSE;
}
