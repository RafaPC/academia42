/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 13:05:39 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/18 17:42:19 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

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
**	Checks for repeated numbers
*/
t_bool	check_stack(int length, int *stack)
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
			{
				ft_printf(STDERR_FILENO,
					"Error\nNumber %i is repeated\n", stack[i]);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

/*
** TODO:
*/
t_bool	get_stack(int length, char **argv, int *stack_a)
{
	int		i;
	int		error_code;

	i = 0;
	while (i < length)
	{
		error_code = ft_custom_atoi(argv[i], &(stack_a[i]), 0, 1);
		if (error_code == -1)
			ft_printf(STDERR_FILENO, "Error\nNumber %s out of int bounds\n",
				argv[i]);
		else if (error_code == -2)
			ft_printf(STDERR_FILENO, "Error\nInvalid character found in '%s'\n",
				argv[i]);
		if (error_code)
			return (false);
		i++;
	}
	if (!check_stack(length, stack_a))
		return (false);
	return (true);
}
