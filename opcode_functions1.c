#include "monty.h"

/**
 * push - adds a new node to the stack
 * @top: pointer to the last node added
 * @line_number: line number in the monty file
 *
 * Return: void
 */

void push(stack_t **top, unsigned int line_number)
{
	stack_t *new_node = NULL;
	char *line;
	int value;

	if (top == NULL)
		return;
	line = read_line(line_number);
	strtok(line, " ");
	value = atoi(strtok(NULL, " "));
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
		return;
	new_node->n = value;
	new_node->next = NULL;
	new_node->prev = *top;
	if (*top != NULL)
		(*top)->next = new_node;
	*top = new_node;

	printf("push -> %d\n", (*top)->n);

	free(line);
}

/**
 * pop - removes the last node of the stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */

void pop(stack_t **top, UNUSED unsigned int line_number)
{
	stack_t *tmp;
	int value;

	if (*top == NULL)
		return;

	value = (*top)->n;
	tmp = *top;

	if ((*top)->prev != NULL)
		(*top)->prev->next = NULL;

	*top = (*top)->prev;

	free(tmp);

	printf("pop  -> %d\n", value);
}

/**
 * pall - prints all the elements on the stack
 *        starting on the top
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */

void pall(stack_t **top, UNUSED unsigned int line_number)
{
	stack_t *tmp;

	tmp = *top;

	for (; tmp != NULL; tmp = tmp->prev)
		printf("%d\n", tmp->n);
}
