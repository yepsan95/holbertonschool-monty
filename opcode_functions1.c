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
	char *line, *word;
	int i, value, only_numbers = 1;

	if (top == NULL)
		return;
	line = strdup((*file_array)[line_number]);
	if (line == NULL)
		malloc_failed();
	word = strtok(line, " ");
	word = strtok(NULL, " ");
	printf("word = %s\n", word);
	if (word != NULL)
	{
		for (i = 0; word[i] != '\0'; i++)
		{
			if (!((word[i] >= '0' && word[i] <= '9')
						|| word[i] == '-'))
				only_numbers = 0;
		}
	}
	if (word == NULL || only_numbers == 0)
	{
		dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_number + 1);
		exit(EXIT_FAILURE);
	}
	value = atoi(word);
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		free(line);
		malloc_failed();
	}
	new_node->n = value;
	new_node->next = NULL;
	new_node->prev = *top;
	if (*top != NULL)
		(*top)->next = new_node;
	*top = new_node;

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

	if (*top == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't pop an empty stack\n", line_number + 1);
                exit(EXIT_FAILURE);
	}

	tmp = *top;
	if ((*top)->prev != NULL)
		(*top)->prev->next = NULL;
	*top = (*top)->prev;

	free(tmp);
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

	if (*top == NULL || top == NULL)
		return;

	tmp = *top;

	for (; tmp != NULL; tmp = tmp->prev)
		printf("%d\n", tmp->n);
}

/**
 * pint - prints the value at the top of the stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */

void pint(stack_t **top, unsigned int line_number)
{
	if (*top == NULL || top == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n", line_number + 1);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*top)->n);
}

/**
 * swap - swaps the two nodes at the top of a stack
 * @top: pointer to the last node of the stack
 * @line_number: line_number in the monty file
 *
 * Return: void
 */
void swap(stack_t **top, UNUSED unsigned int line_number)
{
	stack_t *tmp;

	if ((*top)->prev == NULL || *top == NULL)
	{
		dprintf(STDERR_FILENO,"L%u: can't swap, stack too short\n", line_number + 1);
		exit(EXIT_FAILURE);
	}
	tmp = (*top)->prev;

	(*top)->next = tmp;
	if (tmp->prev != NULL)
	{
		(*top)->prev = tmp->prev;
		tmp->prev->next = *top;
	}
	tmp->next = NULL;
	tmp->prev = *top;

	*top = tmp;
}
