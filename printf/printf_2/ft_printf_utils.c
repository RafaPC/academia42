/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:36:57 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/07 21:05:28 by rprieto-         ###   ########.fr       */
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

char	*ft_strjoin_and_free(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;
	int		j;
	char	*aux;

	aux = (char*)s1;
	if (!s1 || !s2)
		return (!s1) ? (char*)s2 : (char*)s1;
	if (!(joined_str = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
	* sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined_str[j++] = s2[i++];
	joined_str[j] = '\0';
	free(aux);
	return (joined_str);
}

void	print_justification(char c, int times)
{
	while (times > 0)
	{
		write(1, &c, 1);
		times--;
	}
}
