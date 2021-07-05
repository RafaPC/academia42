#include "push_swap.h"

/*
**	Pops the 2 smallest numbers, orders the 3 remaining and
**	pushes back the smallests
*/
void	sort_5_todo(t_stack *stack_a, t_stack *stack_b, const int length)
{
	pop_smaller_number(stack_b, stack_a,
		get_smallest_number(stack_a->numbers, stack_a->length));
	if (length == 5)
		pop_smaller_number(stack_b, stack_a,
			get_smallest_number(stack_a->numbers, stack_a->length));
	if (stack_a->length == 3)
		sort_3_ascending_todo(stack_a, stack_a->numbers);
	else
		sort_3_ascending(stack_a, 3);
	push(stack_a, stack_b, true);
	if (length == 5)
		push(stack_a, stack_b, true);
}

/*
**	Receives the 2 stacks, the stack_b having only 3 numbers
**	and sorts the stack_b
*/
void	sort_3_ascending_todo(t_stack *stack, int *numbers)
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
	else if (numbers[0] < numbers[1]
		&& numbers[0] < numbers[2]
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
**	Receives the 2 stacks, the stack_b having only 3 numbers
**	and sorts the stack_b TODO:
*/
void	sort_3_descending(t_stack *stack, int length)
{
	if (stack->numbers[0] < stack->numbers[1])
		swap(stack, true);
	if (length == 2)
		return ;
	if (stack->numbers[0] > stack->numbers[1]
		&& stack->numbers[0] > stack->numbers[2]
		&& stack->numbers[2] < stack->numbers[0]
		&& stack->numbers[2] < stack->numbers[1])
		return ;
	rotate(stack, true);
	swap(stack, true);
	reverse_rotate(stack, true);
	if (stack->numbers[0] < stack->numbers[1])
		swap(stack, true);
}

/*
**	Receives the 2 stacks, the stack_b having only 3 numbers
**	and sorts the stack_b TODO:
*/
void	sort_3_ascending(t_stack *stack, int length)
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
