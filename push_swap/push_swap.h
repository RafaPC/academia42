/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:12:46 by rprieto-          #+#    #+#             */
/*   Updated: 2021/07/05 16:10:38 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
typedef enum e_stack_id
{
	id_a,
	id_b
}			t_stack_id;


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

void	read_input(t_stack *stack_a, t_stack *stack_b);
/*
**		OPERATIONS
*/
void	print_stacks(t_stack stack_a, t_stack stack_b);
void	swap(t_stack *stack, const t_bool print_instruction);
void	push(t_stack *stack_dst, t_stack *stack_src, const t_bool print_instruction);
void	rotate(t_stack *stack, const t_bool print_instruction);
void	reverse_rotate(t_stack *stack, const t_bool print_instruction);
/*
**		UTILS
*/
t_bool	is_ascending_order(t_stack stack);
t_bool	ft_custom_atoi(const char *str, int *nbr, int i, int sign);
t_bool	initialice_stacks(t_stack *stack_a, t_stack *stack_b, const int length);

/*
**		SORT
*/
void	sort_3_ascending(t_stack *stack, int length);
void	sort_3_a(t_stack *stack, int length);
void	sort_5_todo(t_stack *stack_a, t_stack *stack_b, int length);

/*
**		INPUT UTILS
*/

t_bool	check_number(char *number);
t_bool	stack_is_correct(const int length, const int *stack);
t_bool	get_stack(const int length, const char **argv, int *stack_a);

/*
**		PUSH_SWAP
*/

void	main_sort_stack(t_stack *stack_a, t_stack *stack_b, int length);
void	push_b_to_a_in_order(t_stack *stack_a, t_stack *stack_b,
			int push_counter);

void	juggle_sort_b(t_stacks_info *stacks, int group_length);
void	juggle_sort_a(t_stacks_info *stacks, int rotated_times);
void	sort_3_descending(t_stack *stack, int length);
void	sort_3_ascending_todo(t_stack *stack, int *numbers);

t_bool	check_special_permutations(t_stacks_info *stacks, int *group_length,
int *rotated_times, int *j);

/*
**	PUSH_SWAP_UTILS
*/
void	pop_smaller_number(t_stack *stack_dst, t_stack *stack_src,
const int number_to_pop);
int		get_median(const int *numbers, const int start, const int end);
t_bool	stack_is_overrotated(t_stack *stack, int rotated_times);
int		get_smallest_number(const int *numbers, const int length);

#endif