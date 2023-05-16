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
 * unknown_instruction - prints an error message if the instruction
 *                        read is unknown
 * @n: line number starting with index 0
 * @opcode: the unknown instruction
 *
 * Return: void
 */
void unknown_instruction(unsigned int n, char *opcode)
{
	dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n", n + 1, opcode);
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

/**
 * skip_empty_line - iterates through a file buffer
 *                   and indentifies the empty lines
 *                   so they can be skipped
 * @file_buffer: file buffer to be used
 * @j: pointer to an interator (index of file_buffer)
 *
 * Return: 1 if the line is empty, 0 otherwise
 */
int skip_empty_line(char *file_buffer, unsigned int *j)
{
	int first_char, skip = 0;

	first_char = file_buffer[(*j)];
	if (first_char == '\n')
	{
		(*j)++;
		skip = 1;
	}
	else
	{
		for (; file_buffer[(*j)] != '\0'; (*j)++)
		{
			if (file_buffer[(*j)] == '\n')
			{
				skip = 0;
				(*j)++;
				break;
			}
		}
	}

	return (skip);
}
