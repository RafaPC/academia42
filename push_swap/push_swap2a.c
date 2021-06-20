/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap2a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:18:40 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/20 13:02:52 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Gets the pivot number and checks if the number on top is greater
**	than the pivot (or the pivot itself), if it is, the number
**	is pushed to stack B, if not, the stack is rotated
**	The number of times the stack is pushed and rotated is saved in two variables
*/
static int	push_rotate_a(t_stack *stack_a, t_stack *stack_b, int *group_length,
int *rotated_times)
{
	int	pivot;
	int	i;
	int	pushed_times;

	pushed_times = 0;
	pivot = get_pivot(stack_a->numbers, 0, *group_length);
	i = 0;
	while (i < *group_length)
	{
		if (stack_a->numbers[0] <= pivot)
		{
			push(stack_b, stack_a);
			pushed_times++;
		}
		else
		{
			rotate(stack_a);
			(*rotated_times)++;
		}
		i++;
	}
	*group_length -= pushed_times;
	return (pushed_times);
}

/*
**	Gets the pivot number and checks if the number on top is greater
**	than the pivot (or the pivot itself), if it is, the number
**	is pushed to stack B, if not, the stack is reversely rotated
**	The number of times the stack is pushed and rotated is saved in two variables
*/
static int	push_reverse_rotate_a(t_stack *stack_a, t_stack *stack_b,
int *group_length, int rotated_times)
{
	int	pivot;
	int	pushed_times;

	pivot = get_pivot(stack_a->numbers, stack_a->length - *group_length,
			stack_a->length);
	pushed_times = 0;
	if (rotated_times > (stack_a->length - *group_length))
	{
		while (rotated_times++ < stack_a->length)
			rotate(stack_a);
		rotated_times = 0;
	}
	while (rotated_times > 0)
	{
		reverse_rotate(stack_a);
		if (stack_a->numbers[0] <= pivot)
		{
			push(stack_b, stack_a);
			(*group_length)--;
			pushed_times++;
		}
		rotated_times--;
	}
	return (pushed_times);
}

/*
**	The function receives both stakcs, the length of the group of numbers is working for
**	and a number indicating how many times the group of numbers is rotated (if it is)
**	Wether they are rotated or not, the pivot is taken from the group of numbers
**	and the stack A will be moved (by rotates if it's not rotated or reverse_rotates if it is)
**	and the numbers greater than the pivot (pivot included) will be pushed into the stack B
**	The number of how many times the stack has been pushed and rotated is returned by the functions
**	Then, if the remaining group of numbers is less or equal than 3, then they are ordered
**	if not, the same function will be called again to divide the group of numbers
**	At last, juggle_sort_b is called to order the numbers in the stack B
*/
void	juggle_sort_a(t_stack *stack_a, t_stack *stack_b, int group_length,
int rotated_times)
{
	int	pushed_times;

	if (rotated_times == 0)
		pushed_times = push_rotate_a(stack_a, stack_b, &group_length,
				&rotated_times);
	else
	{
		pushed_times = push_reverse_rotate_a(stack_a, stack_b, &group_length,
				rotated_times);
		rotated_times = 0;
	}
	// if (stack_a->length > stack_a->sorted_numbers + 3 || rotated_times) //FIXME:
	if (group_length > 3)
		juggle_sort_a(stack_a, stack_b, group_length, rotated_times);
	else
	{
		while (rotated_times--)
			reverse_rotate(stack_a);
		if (group_length > 1)
			sort_3_ascending(stack_a, group_length);
	}
	if (pushed_times > 0)
		juggle_sort_b(stack_a, stack_b, pushed_times);
}
