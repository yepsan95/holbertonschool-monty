#include "monty.h"

/**
 * main - entry point
 * @ac: arguments count
 * @av: arguments array
 *
 * Return: 0 on success, -1 on error
 */
int main(int ac, char **av)
{
	char *pathname = av[1], *file_buffer = NULL;
	char **line_array = NULL;
	unsigned int i;
	stack_t *top = NULL;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file_buffer = read_file(pathname);
	line_array = tokenize(file_buffer);
	file_array = &line_array;
	search(file_buffer, line_array, &top);
	for (i = 0; line_array[i] != NULL; i++)
		free(line_array[i]);
	free_stack(&top, 0);
	free(line_array);
	free(file_buffer);

	return (0);
}

/**
 * search - searchs a file for an opcode in a file
 * @file_buffer: buffer with the contents of the file
 * @line_array: array of strings where each is a line
 * @top: head of the stack
 *
 * Return: void
 */
void search(char *file_buffer, char **line_array, stack_t **top)
{
	unsigned int line_number;
	char *opcode;
	int found_opcode;

	for (line_number = 0; (*file_array)[line_number] != NULL; line_number++)
	{
		opcode = strdup((*file_array)[line_number]);
		if (opcode == NULL)
		{
			free(line_array);
			free(file_buffer);
			malloc_failed();
		}
		if (strcmp(opcode, "") == 0 || strtok(opcode, " ") == NULL)
		{
			free(opcode);
			continue;
		}
		del_whitespace(opcode);
		found_opcode = 0;
		execute(opcode, line_number, top, &found_opcode);
		if (found_opcode == 0)
			unknown_instruction(line_number, opcode);
		free(opcode);
	}
}

/**
 * execute - executes and opcode
 * @opcode: opcode to be executed
 * @n: line number in the file
 * @top: top element on the stack
 * @f: its value is 1 if the opcode is found
 *
 * Return: void
 */
void execute(char *opcode, unsigned int n, stack_t **top, int *f)
{
	int i;
	instruction_t functions[] = {
		{"push", push},
		{"pall", pall},
		{"pop", pop},
		{"pint", pint},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"div", div_},
		{"mul", mul},
		{"mod", mod},
		{NULL, NULL},
	};

	for (i = 0; functions[i].opcode != NULL; i++)
	{
		if (strcmp(functions[i].opcode, opcode) == 0)
		{
			(functions[i].f)(top, n);
			*f = 1;
			break;
		}
	}
}

/**
 * read_file - reads the entire content of a file into a buffer
 * @pathname: pathname of the file to read
 *
 * Return: a string containing all the character in the file
 */
char *read_file(char *pathname)
{
	int fd, file_size;
	char *file_buffer = NULL;
	struct stat st;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", pathname);
		exit(EXIT_FAILURE);
	}
	if (fstat(fd, &st) == -1)
		return (NULL);
	file_size = st.st_size;
	file_buffer = malloc((file_size + 1) * sizeof(char));
	if (file_buffer == NULL)
		malloc_failed();
	file_buffer[file_size] = '\0';
	if (read(fd, file_buffer, file_size) == -1)
		return (NULL);

	if (close(fd) == -1)
		return (NULL);

	return (file_buffer);
}

/**
 * tokenize - splits a string into tokens
 *            where each token is a line
 * @file_buffer: buffer containing the string
 *
 * Return: an array of tokens
 */
char **tokenize(char *file_buffer)
{
	char **line_array = NULL;
	char *strtok_arg = file_buffer;
	unsigned int i, j = 0, skip, line_count = 0;

	for (i = 0; file_buffer[i] != '\0'; i++)
	{
		if (file_buffer[i] == '\n')
			line_count++;
	}
	line_array = malloc((line_count + 1) * sizeof(char *));
	if (line_array == NULL)
		malloc_failed();
	for (i = 0; i < line_count; i++)
	{
		if (i > 0)
			strtok_arg = NULL;
		skip = skip_empty_line(file_buffer, &j);
		if (skip == 1)
			line_array[i] = strdup("");
		else
			line_array[i] = strdup(strtok(strtok_arg, "\n"));
		if (line_array[i] == NULL)
		{
			while (i > 0)
			{
				free(line_array[i]);
				i--;
			}
			free(line_array);
			malloc_failed();
		}
	}
	line_array[i] = NULL;

	return (line_array);
}

