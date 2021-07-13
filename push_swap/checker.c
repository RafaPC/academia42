/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:20:37 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/13 17:27:30 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static void	read_input(t_stack *stack_a, t_stack *stack_b);
static void	execute_instruction(t_stack *stack_a, t_stack *stack_b,
				const char *instruction);
static void	execute_more_instructions(t_stack *stack_a, t_stack *stack_b,
				const char *instruction);

int	main(int argc, const char *argv[])
{
	t_stack		stack_a;
	t_stack		stack_b;

	if (argc == 1)
		return (0);
	else if (initialice_stacks(&stack_a, &stack_b, argc - 1)
		&& get_stack(argc - 1, &argv[1], stack_a.numbers))
	{
		read_input(&stack_a, &stack_b);
		if (is_ascending_ordered(stack_a))
			ft_putstr_fd("OK\n", STDOUT_FILENO);
		else
			ft_putstr_fd("KO\n", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("Error\n", STDERR_FILENO);
	if (stack_a.numbers)
		free(stack_a.numbers);
	if (stack_b.numbers)
		free(stack_b.numbers);
	return (0);
}

/*
**	Reads each line using get_next_line() and executes the right instruction
**	until EOF (end of file)
*/
static void	read_input(t_stack *stack_a, t_stack *stack_b)
{
	int		gnl_ctrl;
	char	*buffer;

	gnl_ctrl = get_next_line(STDIN_FILENO, &buffer);
	while (gnl_ctrl == 1)
	{
		execute_instruction(stack_a, stack_b, buffer);
		free(buffer);
		gnl_ctrl = get_next_line(STDIN_FILENO, &buffer);
	}
	if (buffer)
		free(buffer);
	if (gnl_ctrl == -1)
		ft_putstr_fd("Error\n", STDERR_FILENO);
}

/*
**	Compares the string against every instruction
**	If it matches, the instruction is executed
*/
static void	execute_instruction(t_stack *stack_a, t_stack *stack_b,
const char *instruction)
{
	if (!ft_strncmp(instruction, "sa", 3))
		swap(stack_a, false);
	else if (!ft_strncmp(instruction, "sb", 3))
		swap(stack_b, false);
	else if (!ft_strncmp(instruction, "ss", 3))
	{
		swap(stack_a, false);
		swap(stack_b, false);
	}
	else if (!ft_strncmp(instruction, "pa", 3) && stack_b->length >= 1)
		push(stack_a, stack_b, false);
	else if (!ft_strncmp(instruction, "pb", 3) && stack_a ->length >= 1)
		push(stack_b, stack_a, false);
	else if (!ft_strncmp(instruction, "ra", 3))
		rotate(stack_a, false);
	else if (!ft_strncmp(instruction, "rb", 3))
		rotate(stack_b, false);
	else
		execute_more_instructions(stack_a, stack_b, instruction);
}

/*
**	Compares the string against every instruction
**	If it matches, the instruction is executed
*/
static void	execute_more_instructions(t_stack *stack_a, t_stack *stack_b,
const char *instruction)
{
	if (!ft_strncmp(instruction, "rr", 3))
	{
		rotate(stack_a, false);
		rotate(stack_b, false);
	}
	else if (!ft_strncmp(instruction, "rra", 4))
		reverse_rotate(stack_a, false);
	else if (!ft_strncmp(instruction, "rrb", 4))
		reverse_rotate(stack_b, false);
	else if (!ft_strncmp(instruction, "rrr", 4))
	{
		reverse_rotate(stack_a, false);
		reverse_rotate(stack_b, false);
	}
	else
		ft_putstr_fd("Error\n", STDERR_FILENO);
}
