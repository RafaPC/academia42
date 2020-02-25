/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:30:22 by rprieto-          #+#    #+#             */
/*   Updated: 2020/02/20 11:30:22 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     ft_printf(const char *formatString, ...)
{
    va_list     args;
    int         characterSum;

    va_start(args, formatString);
    characterSum = 0;
    while(*formatString)
    {
        if(*formatString == '%')
            format((char *)++formatString, args, &characterSum);
        else
        {
            write(1, formatString, 1);
            characterSum++;
        }
        formatString++;
    }
    return (characterSum);
}

void	format(char *formatString, va_list args, int *characterSum)
{
	t_modifiers modifiers;

    // Si entra aquí se ha encontrado un porcentaje
    while(!isSpecifier(*formatString))
    {
   		// Así que ahora habría que ir recorriendo para adelante guardándose
		// en un struct los flags que se encuentra

        if (*formatString == '-')
			modifiers.left_justified = TRUE;
		else if (*formatString == '0')
			modifiers.zero_padded = TRUE;
		else if (*formatString == '*')
			modifiers.width = va_arg(args, int);
		else if (*(formatString++) == '.')
		// Cuando se encuentra un punto, si lo siguiente que se encuentra es un asterisco
		// iguala la precision al siguiente argumento, si no, hace un atoi al string de formato
			modifiers.precision = (*formatString == '*')
			? va_arg(args, int) : ft_atoi(formatString);
		formatString++;
    }
    if (*formatString == 'c')
    	// Aquí le pasaría el struct como primer argumento
		printChar(va_arg(args, int), characterSum);
	else if (*formatString == 's')
		printString(va_arg(args, char *), characterSum);
	else if (*formatString == 'd')
		printNumber(va_arg(args, int), characterSum);
	else if (*formatString == 'x')
	{
		write(1, "0x", 2);
		(*characterSum) += 2;
		printHex((long int)va_arg(args, void *), characterSum, LOWER_CASE);
	}
	else if (*formatString == 'X')
	{
		write(1, "0x", 2);
		(*characterSum) += (modifiers.sign == 1) ? 2 : 0; 
		printHex((long int)va_arg(args, void *), characterSum, UPPER_CASE);
	}
	else if (*formatString == 'f')
	{
		// printFloat();
	}
	else if (*formatString == 'p')
	{
		(*characterSum) += (modifiers.sign == 1) ? 2 : 0;
		printHex((long int)va_arg(args, void *), characterSum, UPPER_CASE);
	}
}

void    printChar(char c, int *characterSum)
{
    write(1, &c, 1);
	(*characterSum)++;
}

void	printString(char *string, int *characterSum)
{
	while(*string != '\0')
	{
		write(1, string++, 1);
		(*characterSum)++;
	}
}

void	printNumber(int n, int *characterSum)
{
	long int	n_copy;
	char		c;

	n_copy = n;
	if (n_copy < 0)
	{
		n_copy = -n_copy;
		write(1, "-", 1);
		(*characterSum)++;
	}
	if (n_copy > 9)
	{
		printNumber(n_copy / 10, characterSum);
		c = n_copy % 10 + 48;
	}
	else
		c = n_copy + 48;
	write(1, &c, 1);
	(*characterSum)++;
}

void	printHex(long int n, int *characterSum, int letterType)
{
	long int	n_copy;
	char		*hexCharacters = "0123456789abcdef";

	n_copy = n;
	// if (n_copy < 0)
	// {
	// 	n_copy = -n_copy;
	// 	write(1, "-", 1);
	// 	(*characterSum)++;
	// }
	if (n_copy > 15)
	{
		printHex(n_copy / 16, characterSum, letterType);
		write(1, &hexCharacters[n_copy % 16], 1);
	}
	else
		write(1, &hexCharacters[n_copy], 1);
	(*characterSum)++;
}


int main(void)
{
	int number = 23;
    printf("\nNº de carácteres: %d\n", ft_printf("%d %s\n%d %s\nDirección hexadecimal: %x", number,"cosas", 8, "buenas", &number));
    return (0);
}
