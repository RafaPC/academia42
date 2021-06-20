/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:18:40 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/20 13:02:04 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** TODO:
*/
static int	push_rotate_b(t_stack *stack_a, t_stack *stack_b,
int *group_length, int *rotated_times)
{
	int	pivot;
	int	pushed_times;
	int	i;

	pivot = get_pivot(stack_b->numbers, 0, *group_length);
	pushed_times = 0;
	i = 0;
	while (i < *group_length)
	{
		if (stack_b->numbers[0] >= pivot)
		{
			push(stack_a, stack_b);
			pushed_times++;
		}
		else
		{
			rotate(stack_b);
			(*rotated_times)++;
		}
		i++;
	}
	(*group_length) -= pushed_times;
	return (pushed_times);
}

/*
**	TODO:
*/
static int	push_reverse_rotate_b(t_stack *stack_a, t_stack *stack_b,
int *group_length, int rotated_times)
{
	int	pivot;
	int	pushed_times;

	pivot = get_pivot(stack_b->numbers, stack_b->length - *group_length,
			stack_b->length);
	pushed_times = 0;
	if (rotated_times > stack_b->length - rotated_times)
	{
		while (rotated_times++ < stack_b->length)
			rotate(stack_b);
		rotated_times = 0;
	}
	while (rotated_times > 0)
	{
		reverse_rotate(stack_b);
		if (stack_b->numbers[0] >= pivot)
		{
			push(stack_a, stack_b);
			pushed_times++;
			(*group_length)--;
		}
		rotated_times--;
	}
	return (pushed_times);
}

/*
**	Mientras haya más de 3 elementos se saca pivote, y se pushean los números
**	mayores al stack a, una vez hacia delante y otra hacia detrás,
**	para no rotar/desrotar más de lo necesario.
**	En cada iteración se llama a la función que ordena dichos elementos
*/
void	juggle_sort_b(t_stack *stack_a, t_stack *stack_b, int group_length)
{
	int	rotated_times;
	int	pushed_times;

	rotated_times = 0;
	while (group_length > 0)
	{
		pushed_times = 0;
		if (rotated_times == 0)
			pushed_times = push_rotate_b(stack_a, stack_b, &group_length,
					&rotated_times);
		else
		{
			pushed_times = push_reverse_rotate_b(stack_a, stack_b,
					&group_length, rotated_times);
			rotated_times = 0;
		}
		if (pushed_times > 3)
			juggle_sort_a(stack_a, stack_b, pushed_times, 0);
		else if (pushed_times > 1)
			sort_3_ascending(stack_a, pushed_times);
	}
}
