/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:18:40 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/29 11:44:01 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** TODO:
*/
static void	push_rotate(t_stacks_info *stacks, int *group_length,
int *rotated_times)
{
	const int	pivot = get_median(stacks->b.numbers, 0, *group_length);
	int			i;

	i = *group_length;
	while (i > 0)
	{
		if (!check_special_permutations(
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
**	TODO:
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
		check_special_permutations(stacks, group_length, &rotated_times, &j);
		if (stacks->b.numbers[0] >= pivot)
		{
			push(&stacks->a, &stacks->b, true);
			j--;
			(*group_length)--;
		}
	}
}

/*
**	Mientras haya más de 3 elementos se saca pivote, y se pushean los números
**	mayores al stack a, una vez hacia delante y otra hacia detrás,
**	para no rotar/desrotar más de lo necesario. TODO:
**	En cada iteración se llama a la función que ordena dichos elementos
*/
void	juggle_sort_b(t_stacks_info *stacks, int group_length)
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
		juggle_sort_a(stacks, 0);
	}
}
