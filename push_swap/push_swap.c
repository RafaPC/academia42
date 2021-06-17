/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 12:12:16 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/17 22:22:23 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char *argv[])
{
	t_stack		stack_a;
	t_stack		stack_b;
	int			stack_length;

	stack_a.length = argc - 1;
	stack_a.numbers = NULL;
	stack_a.id = id_a;
	stack_b.numbers = NULL;
	stack_b.id = id_b;
	if (argc == 1 || argc == 2)
		ft_printf(STDOUT_FILENO, "Hacen falta minimo dos numeros\n");
	else
	{
		if (ft_strncmp("-g", argv[1], 3) == 0)
		{
			stack_length = ft_atoi(argv[2]);
			ft_putnbr_fd(stack_length, STDOUT_FILENO);
			//TODO:
		}
		else if (get_stack(argc - 1, (char **)(&argv[1]), &stack_a.numbers))
		{
			if (argc - 1 == 2)
				swap(&stack_a);
			else if (argc - 1 == 3)
				sort_3_ascending(&stack_a);
			else
			{
				stack_b.numbers = (int *)malloc(sizeof(int) * argc - 1);
				stack_b.length = 0;
				print_stacks(stack_a, stack_b);
				main_sort_stack(&stack_a, &stack_b, stack_a.length);
				print_stacks(stack_a, stack_b);
			}
		}
	}
	if (stack_a.numbers)
		free(stack_a.numbers);
	if (stack_b.numbers)
		free(stack_b.numbers);
	return (0);
}

void	main_sort_stack(t_stack *stack_a, t_stack *stack_b, int length)
{
	print_stacks(*stack_a, *stack_b);
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
		sort_3_ascending(stack_a);
	else
		main_sort_stack(stack_a, stack_b, stack_a->length);
	print_stacks(*stack_a, *stack_b);
	juggle_sort_b(stack_a, stack_b, push_counter);
}

void	push_b_to_a_in_order(t_stack *stack_a, t_stack *stack_b, int push_counter)
{
	int	first_elem_index;
	int	biggest_number_index;
	int rotated_times = 0;

	while (push_counter > 0)
	{
		if (push_counter <= 3)
		{
			push(stack_a, stack_b);
			push(stack_a, stack_b);
			push(stack_a, stack_b);
			sort_3_ascending(stack_a);
			return ;
		}
		if (rotated_times < 0 || rotated_times > stack_b->length)
			rotated_times = 0;
		first_elem_index = (rotated_times) ? stack_b->length - rotated_times : 0;
		biggest_number_index = first_elem_index;
		for (int push_counter_cp = push_counter; push_counter_cp > 0; push_counter_cp--)
		{
			if (stack_b->numbers[first_elem_index] > stack_b->numbers[biggest_number_index])
				biggest_number_index = first_elem_index;
			first_elem_index++;
			if (first_elem_index == stack_b->length)
				first_elem_index = 0;
		}
		int index_to_push = biggest_number_index;
		if (index_to_push < stack_b->length - index_to_push)
		{
			while (index_to_push-- > 0)
			{
				rotate(stack_b);
				rotated_times++;
			}
		}
		else
		{
			while (index_to_push++ < stack_b->length)
			{
				reverse_rotate(stack_b);
				rotated_times--;
			}
		}
		push(stack_a, stack_b);
		push_counter--;
	}
}
