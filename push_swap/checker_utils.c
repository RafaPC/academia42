/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:42:23 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/08 12:20:22 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>

/*
**	Prints both stacks
*/
void	print_stacks(int length, t_stack stack_a, t_stack stack_b)
{
	int		i;
	int		number_a;
	int		number_b;

	return ; //FIXME:
	i = 0;
	ft_putstr_fd("--------------------------------\n", STDOUT_FILENO);
	while (i < length)
	{
		if (stack_a.length > i)
			number_a = stack_a.numbers[i];
		else
			number_a = 0;
		if (stack_b.length > i)
			number_b = stack_b.numbers[i];
		else
			number_b = 0;
		ft_printf(STDOUT_FILENO, "%i  %i\n", number_a, number_b);
		i++;
	}
	ft_putstr_fd("_  _\na  b\n", STDOUT_FILENO);
}

/*
**	Checks if the stack is in ascending order
*/
t_bool	is_ascending_order(t_stack stack)
{
	int		i;

	i = 1;
	if (stack.length > 1)
	{
		while (i < stack.length)
		{
			if (stack.numbers[i] < stack.numbers[i - 1])
				return (false);
			i++;
		}
	}
	return (true);
}

/*
**	atoi() that sets a variable to false if the number is bigger than an int
*/
int	ft_custom_atoi(const char *str, int *nbr, int i, int sign)
{
	long int	number;

	number = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number == 0)
			number = str[i] - 48;
		else
			number = number * 10 + str[i] - 48;
		i++;
		if ((sign == 1 && number > INT_MAX)
			|| (sign == -1 && number * -1 < INT_MIN))
			return (-1);
	}
	if (str[i] && !ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
		return (-2);
	*nbr = number * sign;
	return (0);
}
