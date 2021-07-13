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
t_bool	is_ascending_ordered(const t_stack stack)
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
	stack_b->numbers = (int *)malloc(length * sizeof(int));
	if (!stack_a->numbers || !stack_b->numbers)
		return (false);
	stack_a->length = length;
	stack_b->length = 0;
	stack_a->id = id_a;
	stack_b->id = id_b;
	return (true);
}

/*
**	Given an array of numbers and the start and end it returns the median
*/
int	get_median(const int *numbers, const int start, const int end)
{
	const int	mean_num_of_swaps = ((end - start) / 2);
	int			swaps;
	int			index;
	int			median;
	int			i;

	index = start;
	swaps = 0;
	median = numbers[index];
	while (swaps != mean_num_of_swaps)
	{
		median = numbers[index++];
		swaps = 0;
		i = start;
		while (i < end)
		{
			if (numbers[i++] <= median)
				swaps++;
		}
		swaps = end - start - swaps;
		if (swaps < 0)
			swaps *= -1;
	}
	return (median);
}

/*
**	Checks if the set of numbers could be returned to the start of the stack
**	with less instructions by rotating instead of reverse rotating
*/
t_bool	stack_is_overrotated(t_stack *stack, int rotated_times)
{
	if (rotated_times > stack->length - rotated_times)
	{
		while (rotated_times++ < stack->length)
			rotate(stack, true);
		return (true);
	}
	else
		return (false);
}

/*
**	Receives an array of numbers and a length and iterates
**	as many times as length, then returns the smallest number
*/
int	get_smallest_number(const int *numbers, const int length)
{
	int	num;
	int	i;

	i = 0;
	num = numbers[0];
	while (i < length)
	{
		if (numbers[i] < num)
			num = numbers[i];
		i++;
	}
	return (num);
}
