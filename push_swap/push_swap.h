/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:12:46 by rprieto-          #+#    #+#             */
/*   Updated: 2021/06/09 18:07:56 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_stack
{
	int		length;
	int		*numbers;
}				t_stack;

typedef enum e_operation
{
			swap_a,
			swap_b,
			swap_both,
			push_a,
			push_b,
			rotate_a,
			rotate_b,
			rotate_both,
			reverse_rotate_a,
			reverse_rotate_b,
			reverse_rotate_both
}			t_operation;
void	read_input(int length, t_stack *stack_a, t_stack *stack_b, t_bool print_stack_status);
/*
**		OPERATIONS
*/
void	print_stacks(int length, t_stack stack_a, t_stack stack_b);
void	swap(t_stack *stack, t_operation instruction);
void	push(t_stack *stack_dst, t_stack *stack_src, t_operation instruction);
void	rotate(t_stack *stack, t_operation instruction);
void	reverse_rotate(t_stack *stack, t_operation instruction);
/*
**		UTILS
*/
t_bool	is_ascending_order(t_stack stack);
int		ft_custom_atoi(const char *str, int *nbr, int i, int sign);
/*
**		SORT
*/
void	sort_3(t_stack *stack);
void	sort_5(t_stack *stack_a, t_stack *stack_b);
void	pop_smaller_number(t_stack *stack_dst, t_stack *stack_src);
int		get_pivot(int *numbers, int start, int end);

/*
**		INPUT UTILS
*/

t_bool	check_number(char *number);
t_bool	check_stack(int length, int *stack);
t_bool	get_stack(int length, char **argv, int **stack_a);

/*
**		PUSH_SWAP
*/

void	main_sort_stack(t_stack *stack_a, t_stack *stack_b, int length);
void	push_b_to_a_in_order(t_stack *stack_a, t_stack *stack_b, int push_counter);

#endif