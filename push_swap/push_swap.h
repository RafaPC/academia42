/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:12:46 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/13 21:26:43 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef enum e_stack_id
{
	id_a,
	id_b
}				t_stack_id;

typedef struct s_stack
{
	int			length;
	int			*numbers;
	t_stack_id	id;
}				t_stack;

typedef struct s_stacks_info
{
	t_stack		a;
	t_stack		b;
	int			sorted_numbers_a;
}		t_stacks_info;

typedef enum e_operation
{
	swap_a,
	swap_b,
	push_a,
	push_b,
	rotate_a,
	rotate_b,
	reverse_rotate_a,
	reverse_rotate_b
}			t_operation;

/*
**		OPERATIONS
*/

void	push(t_stack *stack_dst, t_stack *stack_src,
			const t_bool print_instruction);
void	swap(t_stack *stack, const t_bool print_instruction);
void	rotate(t_stack *stack, const t_bool print_instruction);
void	reverse_rotate(t_stack *stack, const t_bool print_instruction);

/*
**		UTILS
*/

t_bool	is_ascending_ordered(t_stack stack);
t_bool	initialice_stacks(t_stack *stack_a, t_stack *stack_b, const int length);
int		get_median(const int *numbers, const int start, const int end);
t_bool	stack_is_overrotated(t_stack *stack, int rotated_times);
int		get_smallest_number(const int *numbers, const int length);

/*
**		SORT
*/

void	sort_top_3_numbers(t_stack *stack, int length);
void	sort_5_numbers(t_stack *stack_a, t_stack *stack_b, int length);
void	sort_3_length_stack(t_stack *stack, int *numbers);

/*
**		INPUT UTILS
*/

t_bool	get_stack(const int length, const char **argv, int *stack_a);

/*
**		PUSH_SWAP
*/

void	sort_stack_b(t_stacks_info *stacks, int group_length);
void	sort_stack_a(t_stacks_info *stacks, int rotated_times);
t_bool	move_biggest_number_to_a(t_stacks_info *stacks, int *group_length,
			int *rotated_times, int *i);
#endif