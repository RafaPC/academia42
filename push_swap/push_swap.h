/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:12:46 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/20 13:03:37 by rprieto-         ###   ########.fr       */
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

void	read_input(t_stack *stack_a, t_stack *stack_b,
			t_bool print_stack_status);
/*
**		OPERATIONS
*/
void	print_stacks(t_stack stack_a, t_stack stack_b);
void	swap(t_stack *stack);
void	push(t_stack *stack_dst, t_stack *stack_src);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);
/*
**		UTILS
*/
t_bool	is_ascending_order(t_stack stack);
int		ft_custom_atoi(const char *str, int *nbr, int i, int sign);
/*
**		SORT
*/
void	sort_3_ascending(t_stack *stack, int length);
void	sort_5_todo(t_stack *stack_a, t_stack *stack_b, int length);
int		pop_smaller_number(t_stack *stack_dst, t_stack *stack_src);
int		get_pivot(int *numbers, int start, int end);

/*
**		INPUT UTILS
*/

t_bool	check_number(char *number);
t_bool	check_stack(int length, int *stack);
t_bool	get_stack(int length, char **argv, int *stack_a);

/*
**		PUSH_SWAP
*/

void	main_sort_stack(t_stack *stack_a, t_stack *stack_b, int length);
void	push_b_to_a_in_order(t_stack *stack_a, t_stack *stack_b,
			int push_counter);

void	juggle_sort_b(t_stack *stack_a, t_stack *stack_b, int group_length);
void	juggle_sort_a(t_stack *stack_a, t_stack *stack_b, int group_length,
			int rotated_times);
void	sort_3_descending(t_stack *stack, int length);
void	sort_3_ascending_todo(t_stack *stack);

#endif