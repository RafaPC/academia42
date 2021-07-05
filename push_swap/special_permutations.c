/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_permutations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 13:46:48 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/05 11:42:27 by rprieto-         ###   ########.fr       */
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
**	TODO:
*/
t_bool	check_sortedness(t_stacks_info *stacks, int *group_length,
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
**	TODO:
*/
t_bool	can_sort_a(t_stacks_info *stacks, int group_length, int i)
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
**	TODO:
*/
t_bool	check_special_permutations(t_stacks_info *stacks, int *group_length,
int *rotated_times, int *i)
{
	t_bool	done;

	done = false;
	if (can_sort_a(stacks, *group_length, *rotated_times))
	{
		juggle_sort_a(stacks, 0);
		while (*group_length > 0
			&& check_sortedness(stacks, group_length, rotated_times, i))
			done = true;
	}
	return (done);
}
