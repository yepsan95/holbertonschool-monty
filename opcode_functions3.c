#include "monty.h"

/**
 * mod - computes the rest of the division of the
 *       second top element of the stack by the
 *       top element of the stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */
void mod(stack_t **top, unsigned int line_number)
{
	stack_t *tmp;

	if (*top == NULL || top == NULL || (*top)->prev == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't mod, stack too short\n", line_number + 1);
		exit(EXIT_FAILURE);
	}

	tmp = *top;
	if (tmp->n == 0)
	{
		dprintf(STDERR_FILENO, "L%u: division by zero\n", line_number + 1);
		exit(EXIT_FAILURE);
	}
	*top = tmp->prev;
	(*top)->next = NULL;
	(*top)->n = (*top)->n % tmp->n;

	free(tmp);
}
