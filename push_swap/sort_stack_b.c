/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:18:40 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/13 21:03:10 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Gets the median of the group of numbers
**	Then iterates as many times as numbers are in the group
**	Every iteration it tries to move the biggest number from B to A
**	If it achieves it, it skips the current iteration
**	If not, it compares the top number with the median and checks if the number
**	on top is greater (or the pivot itself), if it is, the number
**	is pushed to stack A, if not, the stack is rotated
**	The number of times the stack is pushed and rotated is saved in two variables
*/
static void	push_rotate(t_stacks_info *stacks, int *group_length,
int *rotated_times)
{
	const int	pivot = get_median(stacks->b.numbers, 0, *group_length);
	int			i;

	i = *group_length;
	while (i > 0)
	{
		if (!move_biggest_number_to_a(
				stacks, group_length, rotated_times, &i))
		{
			if (stacks->b.numbers[0] >= pivot)
			{
				push(&stacks->a, &stacks->b, true);
				(*group_length)--;
			}
			else
			{
				rotate(&stacks->b, true);
				(*rotated_times)++;
			}
			i--;
		}
	}
}

/*
**	Gets the median of the group of numbers
**	Then iterates as many times as numbers are in the group
**	Every iteration it tries to move the biggest number from B to A
**	If it achieves it, it skips the current iteration
**	If not, it compares the top number with the median and checks if the number
**	on top is greater (or the pivot itself), if it is, the number
**	is pushed to stack A, if not, the stack is reverse rotated
**	The number of times the stack is pushed and rotated is saved in two variables
*/
static void	push_reverse_rotate(t_stacks_info *stacks, int *group_length,
int rotated_times)
{
	int	pivot;
	int	j;

	j = 0;
	pivot = get_median(stacks->b.numbers, stacks->b.length - *group_length,
			stacks->b.length);
	while (rotated_times > 0)
	{
		reverse_rotate(&stacks->b, true);
		rotated_times--;
		j++;
		move_biggest_number_to_a(stacks, group_length, &rotated_times, &j);
		if (stacks->b.numbers[0] >= pivot)
		{
			push(&stacks->a, &stacks->b, true);
			j--;
			(*group_length)--;
		}
	}
}

/*
**	The function receives both stacks and
**	the length of the group of numbers is working with
**	The pivot is taken from the group of numbers and the stack B will be moved
**	(by rotates if it's not rotated or reverse_rotates if it is) and the numbers
**	greater than the pivot (pivot included) will be pushed into the stack B
**	Each time sort_stack_a() will be called to sort the pushed numbers
**	This is repeated until every number from the group has been pushed
*/
void	sort_stack_b(t_stacks_info *stacks, int group_length)
{
	int	rotated_times;

	rotated_times = 0;
	while (group_length > 0)
	{
		if (rotated_times > stacks->b.length - rotated_times)
		{
			while (rotated_times++ < stacks->b.length)
				rotate(&stacks->b, true);
			rotated_times = 0;
		}
		if (rotated_times == 0)
			push_rotate(stacks, &group_length, &rotated_times);
		else
		{
			push_reverse_rotate(stacks, &group_length, rotated_times);
			rotated_times = 0;
		}
		sort_stack_a(stacks, 0);
	}
}
