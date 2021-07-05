/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:42:23 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/01 12:35:06 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Checks if the stack is in ascending order
*/
t_bool	is_ascending_order(const t_stack stack)
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
** Initialices the stacks variables and checks if malloc() returns NULL pointers
*/
t_bool	initialice_stacks(t_stack *stack_a, t_stack *stack_b, const int length)
{
	stack_a->numbers = (int *)malloc(length * sizeof(int));
	if (!stack_a->numbers)
		return (false);
	stack_b->numbers = (int *)malloc(length * sizeof(int));
	if (!stack_b->numbers)
		return (false);
	stack_a->length = length;
	stack_b->length = 0;
	stack_a->id = id_a;
	stack_b->id = id_b;
	return (true);
}
