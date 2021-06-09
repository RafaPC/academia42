/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:10:22 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/09 18:07:43 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>


/*
**
*/
void print_operation(t_operation operation)
{
	if (operation == swap_a)
		write(STDOUT_FILENO, "sa\n", 3);
	else if (operation == swap_b)
		write(STDOUT_FILENO, "sb\n", 3);
	else if (operation == swap_both)
		write(STDOUT_FILENO, "ss\n", 3);
	else if (operation == push_a)
		write(STDOUT_FILENO, "pa\n", 3);
	else if (operation == push_b)
		write(STDOUT_FILENO, "pb\n", 3);
	else if (operation == rotate_a)
		write(STDOUT_FILENO, "ra\n", 3);
	else if (operation == rotate_b)
		write(STDOUT_FILENO, "rb\n", 3);
	else if (operation == rotate_both)
		write(STDOUT_FILENO, "rr\n", 3);
	else if (operation == reverse_rotate_a)
		write(STDOUT_FILENO, "rra\n", 4);
	else if (operation == reverse_rotate_b)
		write(STDOUT_FILENO, "rrb\n", 4);
	else if (operation == reverse_rotate_both)
		write(STDOUT_FILENO, "rrr\n", 4);
	
}

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
void	push(t_stack *stack_dst, t_stack *stack_src, t_operation instruction)
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
	print_operation(instruction);
}

/*
**	Swaps the first to elements at the top of stack a, b, or both
**	Which stack swaps depends on the mode
*/
void	swap(t_stack *stack, t_operation instruction)
{
	int		aux;

	aux = stack->numbers[0];
	stack->numbers[0] = stack->numbers[1];
	stack->numbers[1] = aux;
	print_operation(instruction);
}

/*
**	Shift up all elements of the stack by 1.
**	The first element becomes the last one.
*/
void	rotate(t_stack *stack, t_operation instruction)
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
	print_operation(instruction);
}

/*
**	Shift down all elements of the stack by 1.
**	The last element becomes the first one.
*/
void	reverse_rotate(t_stack *stack, t_operation instruction)
{
	int		aux;
	int		i;

	i = stack->length - 1;
	if (stack->length > 1)
	{
		aux = stack->numbers[stack->length - 1];
		while (i > 0)
		{
			stack->numbers[i] = stack->numbers[i - 1];
			i--;
		}
		stack->numbers[0] = aux;
	}
	print_operation(instruction);
}
