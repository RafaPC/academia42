/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:20:37 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/18 13:30:49 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_stack		stack_a;
	t_stack		stack_b;
	t_bool		print_stack_status;

	print_stack_status = false;
	stack_a.length = argc - 1;
	stack_a.id = id_a;
	stack_a.numbers = NULL;
	stack_b.numbers = NULL;
	stack_b.id = id_b;
	if (argc == 1 || argc == 2)
		ft_printf(STDOUT_FILENO, "Hacen falta minimo dos numeros\n");
	else
	{
		if (!ft_strncmp("-v", argv[1], 3))
		{
			print_stack_status = true;
			ft_printf(STDOUT_FILENO, "patata\n");
			argv = &argv[1];
		}
		if (get_stack(argc - 1, (char **)(&argv[1]), &stack_a.numbers))
		{
			stack_b.numbers = (int *)malloc(sizeof(int) * argc - 1);
			stack_b.length = 0;
			// read_input(argc - 1, &stack_a, &stack_b, print_stack_status);
			if (stack_a.length == 3)
			{
				push(&stack_b, &stack_a);
				push(&stack_b, &stack_a);
				push(&stack_b, &stack_a);
				sort_3_ascending(&stack_a);
			}
			else if (stack_a.length == 5)
			{
				push(&stack_b, &stack_a);
				push(&stack_b, &stack_a);
				push(&stack_b, &stack_a);
				push(&stack_b, &stack_a);
				push(&stack_b, &stack_a);
				sort_5(&stack_a, &stack_b);
			}
			else
				read_input(&stack_a, &stack_b, print_stack_status);
			if (is_ascending_order(stack_a))
				ft_putstr_fd("OK\n", STDOUT_FILENO);
			else
				ft_putstr_fd("KO\n", STDOUT_FILENO);
		}
	}
	if (stack_a.numbers)
		free(stack_a.numbers);
	if (stack_b.numbers)
		free(stack_b.numbers);
	return (0);
}
