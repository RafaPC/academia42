/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 13:05:39 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/13 17:47:42 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <limits.h>

/*
**	Iterates over the stack taking every number and comparing it
**	with every each other checking if there is one repeated
*/
t_bool	has_repeated_numbers(const int length, const int *numbers)
{
	int		i;
	int		j;

	i = 0;
	while (i < length)
	{
		j = 1;
		while (i + j < length)
		{
			if (numbers[i] == numbers[i + j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

/*
**	atoi() that returns false wether the number exceeds the int limits or
**	the string has doesn't end with a digit
*/
static t_bool	atoi_check_number(const char *str, int *nbr, int i, int sign)
{
	long int	number;

	number = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (number == 0)
			number = str[i] - 48;
		else
			number = number * 10 + str[i] - 48;
		i++;
		if ((sign == 1 && number > INT_MAX)
			|| (sign == -1 && number * -1 < INT_MIN))
			return (false);
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (false);
	*nbr = number * sign;
	return (true);
}

/*
**	Iterates over the arguments from the second element to the last
**	It sends every string to the atoi that inserts the number into the array
**	At the end the stack is iterated through to check if any number is repeated
*/
t_bool	get_stack(const int length, const char **argv, int *numbers)
{
	int		i;

	i = 0;
	while (i < length)
	{
		if (!atoi_check_number(argv[i], &(numbers[i]), 0, 1))
			return (false);
		i++;
	}
	return (!has_repeated_numbers(length, numbers));
}
