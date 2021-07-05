/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:20:37 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/01 20:25:42 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	execute_more_instructions(t_stack *stack_a, t_stack *stack_b,
			char *instruction);

int	main(int argc, const char *argv[])
{
	t_stack		stack_a;
	t_stack		stack_b;

	if (argc == 1)
		return (0);
	else if (initialice_stacks(&stack_a, &stack_b, argc - 1)
		&& get_stack(argc - 1, &argv[1], stack_a.numbers))
	{
		stack_b.numbers = (int *)malloc(sizeof(int) * argc - 1);
		stack_b.length = 0;
		read_input(&stack_a, &stack_b);
		if (is_ascending_order(stack_a))
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
**	Compares the string against every instruction
**	If it matches, the instruction is executed
*/
void	execute_instruction(t_stack *stack_a, t_stack *stack_b,
char *instruction)
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

void	execute_more_instructions(t_stack *stack_a, t_stack *stack_b,
char *instruction)
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

/*
**	FIXME: GNL LEAKS
*/
void	read_input(t_stack *stack_a, t_stack *stack_b)
{
	int		gnl_ctrl;
	char	*buffer;

	gnl_ctrl = get_next_line(STDIN_FILENO, &buffer);
	while (gnl_ctrl == 1)
	{
		execute_instruction(stack_a, stack_b, buffer);
		gnl_ctrl = get_next_line(STDIN_FILENO, &buffer);
	}
	if (gnl_ctrl == -1)
		ft_putstr_fd("Error\n", STDERR_FILENO);
}
