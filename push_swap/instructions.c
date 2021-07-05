/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:10:22 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/29 11:40:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

/*
**	Returns the last element of the stack (last in)
*/
static int	pop(t_stack *stack)
{
	int		number_on_top;
	int		i;

	number_on_top = 0;
	i = 0;
	if (stack->length > 0)
	{
		number_on_top = stack->numbers[0];
		while (i < stack->length - 1)
		{
			stack->numbers[i] = stack->numbers[i + 1];
			i++;
		}
		stack->length--;
	}
	return (number_on_top);
}

/*
**	Pushes an element to the stack
*/
void	push(t_stack *stack_dst, t_stack *stack_src, const t_bool print_instruction)
{
	int	i;

	i = stack_dst->length;
	while (i > 0)
	{
		stack_dst->numbers[i] = stack_dst->numbers[i - 1];
		i--;
	}
	stack_dst->numbers[0] = pop(stack_src);
	stack_dst->length++;
	if (print_instruction)
	{
	if (stack_dst->id == id_a)
		write(STDOUT_FILENO, "pa\n", 3);
	else
		write(STDOUT_FILENO, "pb\n", 3);
	}
}

/*
**	Swaps the first to elements at the top of stack a, b, or both
**	Which stack swaps depends on the mode
*/
void	swap(t_stack *stack, const t_bool print_instruction)
{
	int		aux;

	aux = stack->numbers[0];
	stack->numbers[0] = stack->numbers[1];
	stack->numbers[1] = aux;
	if (print_instruction)
	{
		if (stack->id == id_a)
			write(STDOUT_FILENO, "sa\n", 3);
		else
			write(STDOUT_FILENO, "sb\n", 3);
	}
}

/*
**	Shift up all elements of the stack by 1.
**	The first element becomes the last one.
*/
void	rotate(t_stack *stack, const t_bool print_instruction)
{
	int		aux;
	int		i;

	i = 0;
	if (stack->length > 1)
	{
		aux = stack->numbers[0];
		while (i < stack->length - 1)
		{
			stack->numbers[i] = stack->numbers[i + 1];
			i++;
		}
		stack->numbers[stack->length - 1] = aux;
	}
	if (print_instruction)
	{
		if (stack->id == id_a)
			write(STDOUT_FILENO, "ra\n", 3);
		else
			write(STDOUT_FILENO, "rb\n", 3);
	}
}

/*
**	Shift down all elements of the stack by 1.
**	The last element becomes the first one.
*/
void	reverse_rotate(t_stack *stack, const t_bool print_instruction)
{
	const int	aux = stack->numbers[stack->length - 1];
	int			i;

	i = stack->length - 1;
	while (i > 0)
	{
		stack->numbers[i] = stack->numbers[i - 1];
		i--;
	}
	stack->numbers[0] = aux;
	if (print_instruction)
	{
		if (stack->id == id_a)
			write(STDOUT_FILENO, "rra\n", 4);
		else
			write(STDOUT_FILENO, "rrb\n", 4);
	}
}
