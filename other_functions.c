#include "monty.h"

/**
 * malloc_failed - prints an error message if malloc fails
 *                 and exits the program with status EXIT_FAILURE
 *
 * Return: void
 */
void malloc_failed(void)
{
	perror("Error: malloc failed");
	exit(EXIT_FAILURE);
}

/**
 * free_stack - frees all the nodes in a stack
 * @top: head of the stack
 * @line_number: number of line in the monty file
 *               to be excuted
 * Return: void
 */
void free_stack(stack_t **top, UNUSED unsigned int line_number)
{
	stack_t *tmp;

	if (*top == NULL || top == NULL)
		return;

	while (*top != NULL)
	{
		tmp = *top;
		*top = (*top)->prev;
		free(tmp);
	}
}

/**
 * del_whitespace - deletes all the whitespaces at
 *                  the beggining of a string
 * @str: string
 *
 * Return: void
 */
void del_whitespace(char *str)
{
	int i, offset, whitespaces = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
			whitespaces++;
		else
			break;
	}
	offset = i;
	if (whitespaces > 0)
	{
		for (i = 0; str[i + offset] != '\0'; i++)
			str[i] = str[i + offset];
		str[i] = '\0';
	}
}
