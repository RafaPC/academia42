/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:20:53 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/05 12:16:24 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Given an array of numbers and the start and end, it returns the median
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
**	Receives a destination stack and a source stack and pops the smallest
**	number from the source and pushes it into the destination
*/
void	pop_smaller_number(t_stack *stack_dst, t_stack *stack_src,
const int number_to_pop)
{
	int	i;

	i = 0;
	while (i < stack_src->length)
	{
		if (stack_src->numbers[i] == number_to_pop)
			break ;
		i++;
	}
	while (i--)
		rotate(stack_src, true);
	push(stack_dst, stack_src, true);
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
**	Given the stack A, it iterates through the numbers that are not sorted
**	and returns the smallest
*/
int	get_smallest_number(const int *numbers, const int length)
{
	int			num;
	int			i;

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
