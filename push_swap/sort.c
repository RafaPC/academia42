#include "push_swap.h"

/*
**	Receives a destination stack and a source stack and pops the smallest
**	number from the source and pushes it into the destination
*/
static void	pop_smallest_number(t_stack *stack_dst, t_stack *stack_src,
const int number_to_pop)
{
	int	i;

	i = 0;
	while (i < stack_src->length)
	{
		if (stack_src->numbers[i] == number_to_pop)
			break ;
		i++;
	}
	if (i > stack_src->length - i)
	{
		while (i++ < stack_src->length)
			reverse_rotate(stack_src, true);
	}
	else
	{
		while (i--)
			rotate(stack_src, true);
	}
	push(stack_dst, stack_src, true);
}

/*
**	Pops the 2 smallest numbers, sorts the 3 remaining and
**	pushes back the smallests
*/
void	sort_5_numbers(t_stack *stack_a, t_stack *stack_b, const int length)
{
	pop_smallest_number(stack_b, stack_a,
		get_smallest_number(stack_a->numbers, stack_a->length));
	if (length == 5)
		pop_smallest_number(stack_b, stack_a,
			get_smallest_number(stack_a->numbers, stack_a->length));
	if (stack_a->length == 3)
		sort_3_length_stack(stack_a, stack_a->numbers);
	else
		sort_top_3_numbers(stack_a, 3);
	push(stack_a, stack_b, true);
	if (length == 5)
		push(stack_a, stack_b, true);
}

/*
**	Receives an stack  with only 3 numbers and checks its numbers to sort
**	the stack in ascending order
*/
void	sort_3_length_stack(t_stack *stack, int *numbers)
{
	if (numbers[0] > numbers[1] && numbers[0] > numbers[2])
	{
		if (numbers[1] > numbers[2])
		{
			rotate(stack, true);
			swap(stack, true);
		}
		else
			rotate(stack, true);
	}
	else if (numbers[0] < numbers[1] && numbers[0] < numbers[2]
		&& numbers[1] > numbers[2])
	{
		swap(stack, true);
		rotate(stack, true);
	}
	else if (numbers[0] > numbers[1] || numbers[0] > numbers[2])
	{
		if (numbers[1] > numbers[2])
			reverse_rotate(stack, true);
		else
			swap(stack, true);
	}
}

/*
**	Receives an stack with more than 3 numbers and check its numbers to sort
**	the first 3 numbers in ascending order
*/
void	sort_top_3_numbers(t_stack *stack, int length)
{
	if (stack->numbers[0] > stack->numbers[1])
		swap(stack, true);
	if (length == 2)
		return ;
	if (stack->numbers[0] < stack->numbers[1]
		&& stack->numbers[0] < stack->numbers[2]
		&& stack->numbers[2] > stack->numbers[0]
		&& stack->numbers[2] > stack->numbers[1])
		return ;
	rotate(stack, true);
	swap(stack, true);
	reverse_rotate(stack, true);
	if (stack->numbers[0] > stack->numbers[1])
		swap(stack, true);
}
