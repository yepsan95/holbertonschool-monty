#include "monty.h"

/**
 * main - entry point
 * @ac: number of arguments
 * @av: array of arguments
 *
 * Return: 0 on success, -1 on error
 */
int main(int ac, __attribute__((unused)) char **av)
{
	stack_t *top = NULL;
	int n;

	if (ac < 2)
		return (-1);

	push(&top, 1);
	push(&top, 2);
	push(&top, 3);
	push(&top, 4);
	push(&top, 5);

	for (n = pop(&top); n; n = pop(&top))
		printf("n = %d\n", n);

	return (0);
}

/**
 * push - adds a new node to the stack
 * @top: pointer to the last node added
 * @value: value of the node
 *
 * Return: 1 on success
 */
int push(stack_t **top, int value)
{
	stack_t *new_node = NULL;

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
		return (-1);

	new_node->n = value;
	new_node->next = NULL;
	new_node->prev = *top;
	(*top)->next = new_node;
	*top = new_node;

	printf("%d\n", (*top)->n);

	return (1);
}

/**
 * pop - removes the last node of the stack
 * @top: pointer to the last node of the stack
 *
 * Return: value of the removed node
 */
int pop(stack_t **top)
{
	stack_t *tmp;
	int value;

	if (*top == NULL)
		return (0);

	value = (*top)->n;
	tmp = *top;

	(*top)->prev->next = NULL;
	*top = (*top)->prev;

	free(tmp);

	printf("%d\n", value);

	return (value);
}
