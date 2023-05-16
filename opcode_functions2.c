#include "monty.h"

/**
 * add - adds the top two elements of the stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */

void add(stack_t **top, unsigned int line_number)
{
	stack_t *tmp;

	if (*top == NULL || top == NULL || (*top)->prev == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number + 1);
		exit(EXIT_FAILURE);
	}

	tmp = *top;
	*top = tmp->prev;
	(*top)->next = NULL;
	(*top)->n = (*top)->n + tmp->n;

	free(tmp);
}

/**
 * nop - doesn't do anything
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */

void nop(UNUSED stack_t **top, UNUSED unsigned int line_number)
{
}
