/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 12:12:16 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/20 13:03:41 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Initialices the stacks variables and checks if malloc() returns NULL pointers
*/
int	initialice_stacks(t_stack *stack_a, t_stack *stack_b, int length)
{
	stack_a->numbers = (int *)malloc(length * sizeof(int));
	if (!stack_a->numbers)
		return (0);
	stack_b->numbers = (int *)malloc(length * sizeof(int));
	if (!stack_b->numbers)
		return (0);
	stack_a->length = length;
	stack_b->length = 0;
	stack_a->id = id_a;
	stack_b->id = id_b;
	return (1);
}

int	main(int argc, char *argv[])
{
	t_stack		stack_a;
	t_stack		stack_b;

	if (initialice_stacks(&stack_a, &stack_b, argc - 1)
		&& get_stack(argc - 1, (char **)(&argv[1]), stack_a.numbers))
	{
		if (argc - 1 == 5 || argc -1 == 4)
			sort_5_todo(&stack_a, &stack_b, stack_a.length);
		else if (argc - 1 == 3)
			sort_3_ascending_todo(&stack_a);
		else if (argc - 1 == 2)
		{
			if (stack_a.numbers[0] > stack_a.numbers[1])
				swap(&stack_a);
		}
		else if (argc - 1 > 3)
			main_sort_stack(&stack_a, &stack_b, stack_a.length);
	}
	if (stack_a.numbers)
		free(stack_a.numbers);
	if (stack_b.numbers)
		free(stack_b.numbers);
	return (0);
}

/*
**	TODO:
*/
void	main_sort_stack(t_stack *stack_a, t_stack *stack_b, int length)
{
	int	push_counter;
	int	pivot;
	int	i;

	i = 0;
	push_counter = 0;
	pivot = get_pivot(stack_a->numbers, 0, stack_a->length);
	while (i < length)
	{
		if (stack_a->numbers[0] <= pivot)
		{
			push(stack_b, stack_a);
			push_counter++;
		}
		else
			rotate(stack_a);
		i++;
	}
	if (stack_a->length <= 3)
		sort_3_ascending(stack_a, stack_a->length);
	else
		main_sort_stack(stack_a, stack_b, stack_a->length);
	juggle_sort_b(stack_a, stack_b, push_counter);
}
