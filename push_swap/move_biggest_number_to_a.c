/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_biggest_number_to_a.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 13:46:48 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/13 20:52:46 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Receives an array of numbers and a start and end
**	Iterates from start to end comparing numbers and returns the biggest
*/
static int	get_biggest_num(const int *numbers, const int start, const int end)
{
	int	biggest_num;
	int	i;

	i = start;
	biggest_num = numbers[start];
	while (i < end)
	{
		if (numbers[i] > biggest_num)
			biggest_num = numbers[i];
		i++;
	}
	return (biggest_num);
}

/*
**	Checks where is the biggest number and execute the instructions to
**	move it to the start of the stack and push it to A
*/
t_bool	move_biggest_number(t_stacks_info *stacks, int *group_length,
int *rotated_times, int *i)
{
	const int	biggest_num = get_biggest_num(stacks->b.numbers, 0,
			stacks->b.length);

	if (biggest_num == stacks->b.numbers[stacks->b.length - 1]
		&& *rotated_times > 1)
	{
		(*rotated_times)--;
		(*i)++;
		reverse_rotate(&stacks->b, true);
	}
	else if (biggest_num == stacks->b.numbers[1] && *i > 1)
		swap(&stacks->b, true);
	else if (biggest_num == stacks->b.numbers[0] && *i > 0)
	{
		(*i)--;
		(*group_length)--;
		push(&stacks->a, &stacks->b, true);
		stacks->sorted_numbers_a++;
	}
	else
		return (false);
	return (true);
}

/*
**	Calculates wether the biggest number from B is easy to push to A
*/
t_bool	can_insert_next_number(t_stacks_info *stacks, int group_length, int i)
{
	const int	smallest_number_a = get_smallest_number(stacks->a.numbers,
			stacks->a.length - stacks->sorted_numbers_a);
	const int	biggest_number_b_tail = get_biggest_num(stacks->b.numbers,
		stacks->b.length - i - 1, stacks->b.length);
	int			biggest_number_b;

	biggest_number_b = get_biggest_num(
			stacks->b.numbers, 0, group_length);
	if (biggest_number_b_tail > biggest_number_b)
		biggest_number_b = biggest_number_b_tail;
	return (biggest_number_b < smallest_number_a);
}

/*
**	The first time it checks if the biggest number can be moved easily to A
**	If it can, calls sort_stack_a() and enters a while, if not, returns false
**	Then it iterates until there are no numbers in the group
**	In each iteration tries to move the biggest number from B to
**	the top of the stack or push it to A
**	When the biggest number is no longer easy to move the function ends
*/
t_bool	move_biggest_number_to_a(t_stacks_info *stacks, int *group_length,
int *rotated_times, int *i)
{
	t_bool	done;

	done = false;
	if (can_insert_next_number(stacks, *group_length, *rotated_times))
	{
		sort_stack_a(stacks, 0);
		while (*group_length > 0)
		{
			if (move_biggest_number(stacks, group_length, rotated_times, i))
				done = true;
			else
				return (done);
		}
	}
	return (done);
}
