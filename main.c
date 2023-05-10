#include "monty.h"

char **path;

/**
 * main - entry point
 * @ac: arguments count
 * @av: arguments array
 *
 * Return: 0 on success, -1 on error
 */
int main(int ac, char **av)
{
	char *pathname = av[1];
	stack_t *top = NULL;
	char *line = "", *opcode = NULL;
	int i;
	unsigned int line_number = 0;
	instruction_t functions[] = {
		{"push", push},
		{"pall", pall},
		{"pop", pop},
		{NULL, NULL},
	};

	if (ac != 2)
	{
		printf("Usage: ./a filename\n");
		return (-1);
	}
	path = &pathname;

	line = read_line(line_number);
	for (line_number = 1; line != NULL; line_number++)
	{
		opcode = strtok(line, " ");
		for (i = 0; functions[i].opcode != NULL; i++)
		{
			if (strcmp(functions[i].opcode, opcode) == 0)
			{
				printf("ENCONTRÓ LA FUNCIÓN\n");
				(functions[i].f)(&top, line_number);
				break;
			}
		}
		line = read_line(line_number);
	}

	free(line);

	return (0);
}

/**
 * read_file - reads the entire content of a file
 * @pathname: pathname of the file to read
 * @buffer: buffer to store the contents of the file
 *
 * Return: 0 on success, -1 on error
 */
char *read_line(unsigned int line_number)
{
	FILE *fp;
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	unsigned int line_count = 0;

	fp = fopen((*path), "r");
	if (fp == NULL)
		return (NULL);

	if (getline(&line_buf, &line_buf_size, fp) == -1)
		return (NULL);
	else
	{	
		for (line_count = 1; line_count < line_number; line_count++)
		{
			if (getline(&line_buf, &line_buf_size, fp) == -1)
				return (NULL);
		}
	}

	fclose(fp);

	return (line_buf);
}

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
