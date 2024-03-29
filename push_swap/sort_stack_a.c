/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_a                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:18:40 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/23 16:25:42 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Gets the pivot number and checks if the number on top is greater
**	than the pivot (or the pivot itself), if it is, the number
**	is pushed to stack B, if not, the stack is rotated
**	The number of times the stack is pushed and rotated is saved in two variables
*/
static int	push_rotate(t_stacks_info *stacks, int *rotated_times)
{
	const int	pivot = get_median(
		stacks->a.numbers, 0, stacks->a.length - stacks->sorted_numbers_a);
	int			pushed_times;

	pushed_times = 0;
	while (*rotated_times < stacks->a.length - stacks->sorted_numbers_a)
	{
		if (stacks->a.numbers[0] <= pivot)
		{
			push(&stacks->b, &stacks->a, true);
			pushed_times++;
		}
		else
		{
			rotate(&stacks->a, true);
			(*rotated_times)++;
		}
	}
	return (pushed_times);
}

/*
**	Gets the pivot number and checks if the number on top is greater
**	than the pivot (or the pivot itself), if it is, the number
**	is pushed to stack B, if not, the stack is reversely rotated
**	The number of times the stack is pushed and rotated is saved in two variables
*/
static int	push_reverse_rotate(t_stacks_info *stacks,
int rotated_times)
{
	const int	pivot = get_median(
		stacks->a.numbers, stacks->sorted_numbers_a, stacks->a.length);
	int			pushed_times;

	pushed_times = 0;
	if (stack_is_overrotated(&stacks->a, rotated_times))
		return (0);
	while (rotated_times > 0)
	{
		reverse_rotate(&stacks->a, true);
		rotated_times--;
		if (stacks->a.numbers[0] <= pivot)
		{
			push(&stacks->b, &stacks->a, true);
			pushed_times++;
		}
	}
	return (pushed_times);
}

/*
**	The function receives both stacks, how many numbers are ordered in stack A
**	and a number indicating how many times A has been rotated
**	Wether they are rotated or not, the pivot is taken from the group of
**	numbers and the stack A will be moved (by rotates if it's not rotated or
**	reverse_rotates if it is) and the numbers greater than the
**	pivot (pivot included) will be pushed into the stack B
**	Then if there are more than 3 not ordered numbers
**	the same function will be called again, if not the remaining
**	not ordered numbers will be ordered by sort_3_top_numbers() 
**	At last, sort_stack_b is called to order the numbers in the stack B
*/
void	sort_stack_a(t_stacks_info *stacks, int rotated_times)
{
	int	pushed_times;

	pushed_times = 0;
	if (stacks->a.length - stacks->sorted_numbers_a > 3 || rotated_times)
	{
		if (rotated_times == 0)
			pushed_times = push_rotate(stacks, &rotated_times);
		else
		{
			pushed_times = push_reverse_rotate(stacks, rotated_times);
			rotated_times = 0;
		}
	}
	if ((stacks->a.length - stacks->sorted_numbers_a > 3) || rotated_times)
		sort_stack_a(stacks, rotated_times);
	else
	{
		sort_top_3_numbers(&stacks->a,
			stacks->a.length - stacks->sorted_numbers_a);
		stacks->sorted_numbers_a += stacks->a.length - stacks->sorted_numbers_a;
	}
	if (pushed_times > 0)
		sort_stack_b(stacks, pushed_times);
}
