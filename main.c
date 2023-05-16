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
	char *opcode = NULL;
	char **line_array = NULL;
	int i, found_opcode;
	stack_t *top = NULL;
	unsigned int line_number = 0;
	instruction_t functions[] = {
		{"push", push},
		{"pall", pall},
		{"pop", pop},
		{"pint", pint},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL},
	};

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_buffer = read_file(pathname);
	line_array = tokenize(file_buffer);
	file_array = &line_array;

	printf("MAIN:\n\n");
	for (i = 0; line_array[i] != NULL; i++)
		printf("%s\n", line_array[i]);
	printf("\n----------\n\n");

	for (line_number = 0; (*file_array)[line_number] != NULL; line_number++)
	{
		printf("line number: %d\n", line_number + 1);
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
		printf("opcode: %s\n", opcode);
		del_whitespace(opcode);
		found_opcode = 0;
		for (i = 0; functions[i].opcode != NULL; i++)
		{
			if (strcmp(functions[i].opcode, opcode) == 0)
			{
				(functions[i].f)(&top, line_number);
				found_opcode = 1;
				break;
			}
		}
		if (found_opcode == 0)
		{
			dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n", line_number + 1, opcode);
			exit(EXIT_FAILURE);
		}
		printf("The opcode <%s> has been freed\n", opcode);
		free(opcode);
	}
	for (i = 0; line_array[i] != NULL; i++)
		free(line_array[i]);
	free_stack(&top, 0);
	free(line_array);
	free(file_buffer);

	return (0);
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

	printf("READ:\n\n%s\n", file_buffer);
	printf("\n----------\n\n");

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
	char *strtok_arg;
	unsigned int i, j = 0, skip, line_count = 0;

	for (i = 0; file_buffer[i] != '\0'; i++)
	{
		if (file_buffer[i] == '\n')
			line_count++;
	}
	printf("line_count: %u\n", line_count);
	line_array = malloc((line_count + 1) * sizeof(char *));
	if (line_array == NULL)
		malloc_failed();
	strtok_arg = file_buffer;
	for (i = 0; i < line_count; i++)
	{
		if (i > 0)
			strtok_arg = NULL;
		skip = skip_empty_line(file_buffer, &j);
		if (skip == 1)
		{
			line_array[i] = strdup("");
			printf("line number: %u is empty\n", i + 1);
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
			continue;
		}
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

	printf("TONEKIZE:\n\n");
	for (i = 0; line_array[i] != NULL; i++)
		printf("%s\n", line_array[i]);
	printf("\n----------\n\n");

	return (line_array);
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
