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

	for (i = 0; (*file_array)[i] != NULL; i++)
		printf("array[%d] == %s\n", i, (*file_array)[i]);

	for (line_number = 0; (*file_array)[line_number] != NULL; line_number++)
	{
		opcode = strdup((*file_array)[line_number]);
		if (opcode == NULL)
		{
			free(line_array);
			free(file_buffer);
			malloc_failed();
		}
		if (strcmp(opcode, "") == 0)
		{
			free(opcode);
			continue;
		}
		strtok(opcode, " ");
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
	unsigned int i, j = 0, skip, line_count = 0;

	for (i = 0; file_buffer[i] != '\0'; i++)
	{
		if (file_buffer[i] == '\n')
			line_count++;
	}
	line_array = malloc((line_count + 1) * sizeof(char *));
	if (line_array == NULL)
		malloc_failed();
	skip = skip_empty_line(file_buffer, &j);
	line_array[0] = strdup(strtok(file_buffer, "\n"));
	if (line_array[0] == NULL)
	{
		free(line_array);
		malloc_failed();
	}
	for (i = 1; i < line_count; i++)
	{
		skip = skip_empty_line(file_buffer, &j);
		if (skip == 1)
		{
			line_array[i] = strdup("");
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
		line_array[i] = strdup(strtok(NULL, "\n"));
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
	int skip = 0;

	for (; file_buffer[*j] != '\0'; (*j)++)
	{
		if (file_buffer[*j] == '\n')
		{
			if (file_buffer[(*j) + 1] == '\n')
				skip = 1;
			else
				skip = 0;
			(*j)++;
			break;
		}
	}

	return (skip);
}
