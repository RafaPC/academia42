/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_read_instructions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:12:00 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/06 23:08:05 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include <stdio.h>

void	read_instruction(t_stack *stack_a, t_stack *stack_b, char *instruction)
{
	if (!ft_strncmp(instruction, "sa", 3))
		swap(stack_a, swap_a);
	else if (!ft_strncmp(instruction, "sb", 3))
		swap(stack_b, swap_b);
	else if (!ft_strncmp(instruction, "ss", 3))
	{
		swap(stack_a, swap_a);
		swap(stack_b, swap_b);
	}
	else if (!ft_strncmp(instruction, "pa", 3) && stack_b->length >= 1)
		push(stack_a, stack_b, push_a);
	else if (!ft_strncmp(instruction, "pb", 3) && stack_a ->length >= 1)
		push(stack_b, stack_a, push_b);
	else if (!ft_strncmp(instruction, "ra", 3))
		rotate(stack_a, rotate_a);
	else if (!ft_strncmp(instruction, "rb", 3))
		rotate(stack_b, rotate_b);
	else if (!ft_strncmp(instruction, "rr", 3))
	{
		rotate(stack_a, rotate_a);
		rotate(stack_b, rotate_b);
	}
	else if (!ft_strncmp(instruction, "rra", 4))
		reverse_rotate(stack_a, reverse_rotate_a);
	else if (!ft_strncmp(instruction, "rrb", 4))
		reverse_rotate(stack_b, reverse_rotate_b);
	else if (!ft_strncmp(instruction, "rrr", 4))
	{
		reverse_rotate(stack_a, reverse_rotate_a);
		reverse_rotate(stack_b, reverse_rotate_b);
	}
	else
		ft_printf(STDERR_FILENO, "Error\nUnvalid operation\n");
}

/*
**	FIXME: GNL LEAKS
*/
void	read_input(int length, t_stack *stack_a, t_stack *stack_b, t_bool print_stack_status)
{
	int		gnl_ctrl;
	char	*buffer;

	gnl_ctrl = get_next_line(STDIN_FILENO, &buffer);
	while (gnl_ctrl == 1)
	{
		read_instruction(stack_a, stack_b, buffer);
		if (print_stack_status)
			print_stacks(length, *stack_a, *stack_b);
		gnl_ctrl = get_next_line(STDIN_FILENO, &buffer);
	}
	if (gnl_ctrl == -1)
		ft_putstr_fd("Error\nError while reading\n", STDERR_FILENO);
}
