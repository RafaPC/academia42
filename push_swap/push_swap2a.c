/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap2a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:18:40 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/18 18:43:25 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** TODO:
*/
int	push_rotate_a(t_stack *stack_a, t_stack *stack_b, int *group_length, int *pushed_times)
{
	int	pivot;
	int rotated_times;
	int	i;

	pivot = get_pivot(stack_a->numbers, 0, *group_length);
	rotated_times = 0;
	i = 0;
	int group_length_cp = *group_length; //FIXME:
	while (i < group_length_cp)
	{
		if (stack_a->numbers[0] <= pivot)
		{
			push(stack_b, stack_a);
			(*group_length)--;
			(*pushed_times)++;
		}
		else
		{
			rotate(stack_a);
			rotated_times++;
		}
		i++;
	}
	return (rotated_times);
}

/*
**	TODO:
*/
void	push_reverse_rotate_a(t_stack *stack_a, t_stack *stack_b, int *group_length, int rotated_times, int *pushed_times)
{
	int	pivot;

	pivot = get_pivot(stack_a->numbers, stack_a->length - *group_length, stack_a->length);
	while (rotated_times > 0)
	{
		reverse_rotate(stack_a);
		if (stack_a->numbers[0] <= pivot)
		{
			push(stack_b, stack_a);
			(*group_length)--;
			(*pushed_times)++;
		}
		rotated_times--;
	}
}

/*
**	Mientras haya más de 3 elementos se saca pivote, y se pushean los números mayores
**	al stack a, una vez hacia delante y otra hacia detrás, para no rotar/desrotar más de lo necesario.
**	En cada iteración se llama a la función que ordena dichos elementos
*/
void	juggle_sort_a(t_stack *stack_a, t_stack *stack_b, int group_length, int rotated_times)
{
	int	pushed_times;

	pushed_times = 0;
	if (rotated_times == 0)
		rotated_times = push_rotate_a(stack_a, stack_b, &group_length, &pushed_times);
	else
	{
		push_reverse_rotate_a(stack_a, stack_b, &group_length, rotated_times, &pushed_times);
		rotated_times = 0;
	}
	if (group_length > 3)
		juggle_sort_a(stack_a, stack_b, group_length, rotated_times);
	else
	{
		while (rotated_times--)
			reverse_rotate(stack_a);
		if (group_length == 3)
			sort_3_ascending(stack_a);
		else if (group_length == 2 && stack_a->numbers[0] > stack_a->numbers[1])
			swap(stack_a);
	}
	juggle_sort_b(stack_a, stack_b, pushed_times);
}
