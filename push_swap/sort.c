/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:42:25 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/06 23:11:53 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**		Receives a destination stack and a source stack and pops the smallest
**		number from the source and pushes it into the destination
*/
void	pop_smaller_number(t_stack *stack_dst, t_stack *stack_src)
{
	int	i;
	int	j;
	int	number_cmp;

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
	while (j--)
		rotate(stack_src, rotate_b);
	push(stack_dst, stack_src, push_a);
}

/*
**		Saca los dos números más pequeños, ordena los que quedan como 3, y vuelve a meter los que había sacado
*/
void	sort_5(t_stack *stack_a, t_stack *stack_b)
{
	pop_smaller_number(stack_a, stack_b);
	pop_smaller_number(stack_a, stack_b);
	print_stacks(5, *stack_a, *stack_b);
	sort_3(stack_a);
	print_stacks(5, *stack_a, *stack_b);
	push(stack_b, stack_a, push_b);
	push(stack_b, stack_a, push_b);
}

/*
**		Receives the 2 stacks, the stack_b having only 3 numbers
**		and sorts the stack_b
*/
void	sort_3(t_stack *stack)
{
	if (stack->numbers[0] > stack->numbers[1]
		&& stack->numbers[0] > stack->numbers[2])
	{
		//321 y 312
		//rb sb y rb
		//así siempre se hace rotate de b y si n2 > n3 entonces también se hace un swap de b
		if (stack->numbers[1] > stack->numbers[2])
		{
			rotate(stack, rotate_a);
			swap(stack, swap_a);
		}
		else
			rotate(stack, rotate_a);
	}
	else if (stack->numbers[0] < stack->numbers[1] && stack->numbers[0] < stack->numbers[2]
			&& stack->numbers[1] > stack->numbers[2])
	{
		// swap rotate
		swap(stack, swap_a);
		rotate(stack, rotate_a);
	}
	else if (stack->numbers[0] > stack->numbers[1] || stack->numbers[0] > stack->numbers[2])
	{
		if (stack->numbers[1] > stack->numbers[2]) // rrb
			reverse_rotate(stack, reverse_rotate_a);
		else //sb
			swap(stack, swap_a);
	}
}

/*
**
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
