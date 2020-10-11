/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:01:23 by rprieto-          #+#    #+#             */
/*   Updated: 2020/10/11 13:10:58 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
int		ft_printf(const char *format_string, ...)
{
	va_list	args;
	int		char_sum;

	va_start(args, format_string);
	char_sum = 0;
	while (*format_string)
	{
		if (*format_string == '%')
			format_string = format(args, (char *)++format_string, &char_sum);
		else
			char_sum += write(1, format_string, 1);
		format_string++;
	}
	return (char_sum);
}

char	*format(va_list args, char *format_string, int *char_sum)
{
	t_modifiers modifiers;

	modifiers = ft_initialize_struct();
	while (!is_specifier(*format_string))
	{
		if (*format_string == '-')
			modifiers.left_justified = TRUE;
		else if (*format_string == '0')
			modifiers.zero_padded = TRUE;
		else if (*(format_string) == '.')
			get_precision(args, &format_string, &modifiers);
		else if (*(format_string) == ' ')
			*char_sum += write(1, " ", 1);
		else if (*format_string == '*')
			modifiers.width = va_arg(args, int);
		else
		{
			modifiers.width = ft_atoi(format_string);
			while (ft_isdigit(*(format_string + 1)))
				format_string++;
			//Esto hace que pase de las 15 lineas
			if (modifiers.width < 0)
			{
				modifiers.width = -modifiers.width;
				modifiers.left_justified = TRUE;
			}
		}
		format_string++;
	}
	format2(args, *format_string, modifiers, char_sum);
	return (format_string);
}

void	format2(va_list args, char specifier, t_modifiers modifiers, int *char_sum)
{
	char *string;
	char *format_string;

	if (specifier != 's' && specifier != 'c')
	{
		string = "hola";
		format_string = modifiers_to_string(modifiers);
		*char_sum = ft_printf(format_string, string);
		free(string);
		free(format_string);
	}
	else if (specifier == 'c')
		print_char(va_arg(args, int), modifiers, char_sum);
	else
		handle_string(va_arg(args, char*), modifiers, char_sum);
}

char	*modifiers_to_string(t_modifiers modifiers)
{
	char	*string;
	//En vez de que el join sea una copia del join pero que libere memoria
	// puede ser una funcion que se guarda el auxiliar, llama al join, libera y returnea
	string = ft_strdup("%");
	if (modifiers.left_justified)
		string = ft_strjoin_and_free(string, "-");
	if (modifiers.zero_padded)
		string = ft_strjoin_and_free(string, "0");
	if (modifiers.width)
		string = ft_strjoin_and_free(string, ft_itoa(modifiers.width));
	if (modifiers.precision != -2)
	{
		string = ft_strjoin_and_free(string, ".");
	 	string = ft_strjoin_and_free(string, ft_itoa(modifiers.precision));
	}
	string = ft_strjoin_and_free(string, "s");
	return (string);
}

void	handle_string(char *string, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.precision != -1 || string == NULL)
	{
		if (string == NULL)
			string = "(null)";
		print_string(string, modifiers, char_sum);
	}
}

void	print_string(char *string, t_modifiers modifiers, int *char_sum)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	if (modifiers.precision >= 0)
		len = ((int)ft_strlen(string) < modifiers.precision) ? (int)ft_strlen(string) : modifiers.precision;
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

void print_char(char c, t_modifiers modifiers, int *char_sum)
{
	if (modifiers.width > 1)
	{
		*char_sum += modifiers.width;
		if (modifiers.left_justified == FALSE)
			print_justification((modifiers.zero_padded) ? '0' : ' ', modifiers.width - 1);
		write(1, &c, 1);
		// Aquí hago que si está justificado a la izquierda imprima espacios, o sea que suda de los ceros
		if (modifiers.left_justified == TRUE)
			print_justification((modifiers.zero_padded) ? '0' : ' ', modifiers.width - 1);
	}
	else {
		write(1, &c, 1);
		(*char_sum)++;
	}
}