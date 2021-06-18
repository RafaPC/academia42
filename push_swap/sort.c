/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:42:25 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/18 18:21:56 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**		Receives a destination stack and a source stack and pops the smallest
**		number from the source and pushes it into the destination
*/
int	pop_smaller_number(t_stack *stack_dst, t_stack *stack_src)
{
	int	i;
	int	j;
	int	number_cmp;
	int	rotated_times;

	i = 1;
	j = 0;
	number_cmp = stack_src->numbers[0];
	while (i < stack_src->length)
	{
		if (stack_src->numbers[i] < number_cmp)
		{
			number_cmp = stack_src->numbers[i];
			j = i;
		}
		i++;
	}
	rotated_times = j;
	while (j--)
		rotate(stack_src);
	push(stack_dst, stack_src);
	return (rotated_times);
}

/*
**		Saca los dos números más pequeños, ordena los que quedan como 3, y vuelve a meter los que había sacado
*/
void	sort_5_todo(t_stack *stack_dst, t_stack *stack_aux)
{
	int rotated_times;

	rotated_times =  pop_smaller_number(stack_aux, stack_dst);
	rotated_times += pop_smaller_number(stack_aux, stack_dst);
	sort_3_ascending(stack_dst);
	// if (stack_dst->length > 3)
	// {
	// 	while (rotated_times--)
	// 		reverse_rotate(stack_dst);
	// }
	push(stack_dst, stack_aux); //FIXME: esto supone que stack_dst es A y stack_aux B
	push(stack_dst, stack_aux);
}

/*
**		Receives the 2 stacks, the stack_b having only 3 numbers
**		and sorts the stack_b
*/
void	sort_3_ascending_todo(t_stack *stack)
{
	if (stack->numbers[0] > stack->numbers[1]
		&& stack->numbers[0] > stack->numbers[2])
	{
		//321 y 312
		//rb sb y rb
		//así siempre se hace rotate de b y si n2 > n3 entonces también se hace un swap de b
		if (stack->numbers[1] > stack->numbers[2])
		{
			rotate(stack);
			swap(stack);
		}
		else
			rotate(stack);
	}
	else if (stack->numbers[0] < stack->numbers[1] && stack->numbers[0] < stack->numbers[2]
			&& stack->numbers[1] > stack->numbers[2])
	{
		// swap rotate
		swap(stack);
		rotate(stack);
	}
	else if (stack->numbers[0] > stack->numbers[1] || stack->numbers[0] > stack->numbers[2])
	{
		if (stack->numbers[1] > stack->numbers[2]) // rrb
			reverse_rotate(stack);
		else //sb
			swap(stack);
	}
}

/*
**		Receives the 2 stacks, the stack_b having only 3 numbers
**		and sorts the stack_b TODO:
*/
void	sort_3_descending(t_stack *stack)
{
	if (stack->numbers[0] < stack->numbers[1])
		swap(stack);
	if (stack->numbers[0] > stack->numbers[1] && stack->numbers[0] > stack->numbers[2]
	&& stack->numbers[2] < stack->numbers[0] && stack->numbers[2] < stack->numbers[1])
		return ;
	rotate(stack);
	swap(stack);
	reverse_rotate(stack);
	if (stack->numbers[0] < stack->numbers[1])
		swap(stack);
}

/*
**		Receives the 2 stacks, the stack_b having only 3 numbers
**		and sorts the stack_b TODO:
*/
void	sort_3_ascending(t_stack *stack)
{
	if (stack->numbers[0] > stack->numbers[1])
		swap(stack);
	if (stack->numbers[0] < stack->numbers[1] && stack->numbers[0] < stack->numbers[2]
	&& stack->numbers[2] > stack->numbers[0] && stack->numbers[2] > stack->numbers[1])
		return ;
	rotate(stack);
	swap(stack);
	reverse_rotate(stack);
	if (stack->numbers[0] > stack->numbers[1])
		swap(stack);
}

/*
**	TODO:
*/
int		get_pivot(int *numbers, int start, int end)
{
	int	swaps;
	int	index;
	int	pivot;
	int	mean_num_of_swaps;
	int	i;

	index = start;
	mean_num_of_swaps = ((end - start) / 2);
	swaps = 0;
	pivot = numbers[index];
	while (swaps != mean_num_of_swaps)
	{
		pivot = numbers[index++];
		swaps = 0;
		i = start;
		while (i < end)
		{
			if (numbers[i++] <= pivot)
				swaps++;
		}
		swaps = end - start - swaps;
		if (swaps < 0)
			swaps *= -1;
	}
	return (pivot);
}
