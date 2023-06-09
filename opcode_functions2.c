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


/**
 * sub - substracts the top element of the stack
 *       from the second top element of the stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */
void sub(stack_t **top, unsigned int line_number)
{
	stack_t *tmp;

	if (*top == NULL || top == NULL || (*top)->prev == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't sub, stack too short\n", line_number + 1);
		exit(EXIT_FAILURE);
	}

	tmp = *top;
	*top = tmp->prev;
	(*top)->next = NULL;
	(*top)->n = (*top)->n - tmp->n;

	free(tmp);
}

/**
 * div_ - divides the second top element of the stack
 *       by the top element of the stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */
void div_(stack_t **top, unsigned int line_number)
{
	stack_t *tmp;

	if (*top == NULL || top == NULL || (*top)->prev == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't div, stack too short\n", line_number + 1);
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
	(*top)->n = (*top)->n / tmp->n;

	free(tmp);
}


/**
 * mul - multiplies the second top element of the stack
 *       with the top element of the stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */
void mul(stack_t **top, unsigned int line_number)
{
	stack_t *tmp;

	if (*top == NULL || top == NULL || (*top)->prev == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't mul, stack too short\n", line_number + 1);
		exit(EXIT_FAILURE);
	}

	tmp = *top;
	*top = tmp->prev;
	(*top)->next = NULL;
	(*top)->n = (*top)->n * tmp->n;

	free(tmp);
}
