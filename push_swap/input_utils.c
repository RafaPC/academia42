/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 13:05:39 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/01 19:52:11 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <limits.h>

/*
**	Recibe un string y checkea si es un número o no
*/
t_bool	check_number(char *number)
{
	while (*number)
	{
		if (!ft_isdigit(*number) && *number != '+' && *number != '-')
			return (false);
		number++;
	}
	return (true);
}

/*
**	Iterates over the stack taking every number and comparing it
**	with every each other checking if there is one repeated
*/
t_bool	stack_is_correct(const int length, const int *stack)
{
	int		i;
	int		j;

	i = 0;
	while (i < length)
	{
		j = 1;
		while (i + j < length)
		{
			if (stack[i] == stack[i + j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/*
**	Iterates over the arguments from the second element to the last
**	It sends every string to the atoi that inserts the number into the array
**	At the end the stack is iterated through to check if any number is repeated
*/
t_bool	get_stack(const int length, const char **argv, int *numbers_a)
{
	int		i;

	i = 0;
	while (i < length)
	{
		if (!ft_custom_atoi(argv[i], &(numbers_a[i]), 0, 1))
			return (false);
		i++;
	}
	return (stack_is_correct(length, numbers_a));
}

/*
**	atoi() that sets a variable to false if the number is bigger than an int
*/
t_bool	ft_custom_atoi(const char *str, int *nbr, int i, int sign)
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
	if (str[i] && !ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
		return (false);
	*nbr = number * sign;
	return (true);
}
