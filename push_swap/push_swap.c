/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 12:12:16 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/05 16:36:47 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, const char *argv[])
{
	t_stacks_info	stacks;

	stacks.sorted_numbers_a = 0;
	if (initialice_stacks(&stacks.a, &stacks.b, argc - 1)
		&& get_stack(argc - 1, &argv[1], stacks.a.numbers)
		&& !is_ascending_order(stacks.a))
	{
		if (argc - 1 == 5 || argc - 1 == 4)
			sort_5_todo(&stacks.a, &stacks.b, stacks.a.length);
		else if (argc - 1 == 3)
			sort_3_ascending_todo(&stacks.a, stacks.a.numbers);
		else if (argc - 1 == 2)
		{
			if (stacks.a.numbers[0] > stacks.a.numbers[1])
				swap(&stacks.a, true);
		}
		else if (argc - 1 > 3)
			juggle_sort_a(&stacks, 0);
	}
	if (stacks.a.numbers)
		free(stacks.a.numbers);
	if (stacks.b.numbers)
		free(stacks.b.numbers);
	return (0);
}
