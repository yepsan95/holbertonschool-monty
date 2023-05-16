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

/**
 * pchar - prints the char at the top of the stack,
 *         followed by a new line
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */
void pchar(stack_t **top, unsigned int line_number)
{
	char *error = ": can't pchar, value out of range";

	if (*top == NULL || top == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't pchar, stack empty\n", line_number + 1);
		exit(EXIT_FAILURE);
	}

	if ((*top)->n < 1 || (*top)->n > 126)
	{
		dprintf(STDERR_FILENO, "L%u%s%n", line_number + 1, error);
		exit(EXIT_FAILURE);
	}

	putchar((*top)->n);
	putchar(10);
}
