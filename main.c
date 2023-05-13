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
	char *pathname = av[1];
	char *file_buffer = NULL;
	char **line_array = NULL;
	int i;
	stack_t *top = NULL;
	char *opcode = NULL;
	unsigned int line_number = 0;
	instruction_t functions[] = {
		{"push", push},
		{"pall", pall},
		{"pop", pop},
		{NULL, NULL},
	};

	if (ac != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_buffer = read_file(pathname);
	line_array = tokenize(file_buffer);
	file_array = &line_array;

	printf("main:\n\n");

	for (i = 0; (*file_array)[i] != NULL; i++)
		printf("%s\n", (*file_array)[i]);
	printf("\n----------\n\n");
	printf("program execution:\n\n");

	for (line_number = 0; (*file_array)[line_number] != NULL; line_number++)
	{
		opcode = strdup((*file_array)[line_number]);
		if (opcode == NULL)
			return (-1);
		strtok(opcode, " ");
		printf("LÍNEA LEÍDA: %s\n\n", (*file_array)[line_number]);
		printf("OPCODE %s\n\n", opcode);
		for (i = 0; functions[i].opcode != NULL; i++)
		{
			if (strcmp(functions[i].opcode, opcode) == 0)
			{
				printf("ENCONTRÓ LA FUNCIÓN\n\n");
				(functions[i].f)(&top, line_number);
				break;
			}
		}
		free(opcode);
	}

	printf("<<SALIÓ DEL BUCLE>>\n\n");
	for (i = 0; line_array[i] != NULL; i++)
	{
		printf("%02d -> %s\n", i, line_array[i]);
		free(line_array[i]);
	}
	printf("\nFUERA DEL FOR\n\n");

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
		perror("Error: Can't open file %s", pathname);
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

	printf("\nread_file:\n\n%s", file_buffer);
	printf("\n----------\n\n");

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
	unsigned int i, line_count = 0;

	for (i = 0; file_buffer[i] != '\0'; i++)
	{
		if (file_buffer[i] == '\n')
			line_count++;
	}
	line_array = malloc((line_count + 1) * sizeof(char *));
	if (line_array == NULL)
		malloc_failed();
	line_array[0] = strdup(strtok(file_buffer, "\n"));
	if (line_array[0] == NULL)
	{
		free(line_array);
		malloc_failed();
	}
	for (i = 1; i < line_count; i++)
	{
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

	printf("tokenize:\n\n");

	for (i = 0; line_array[i] != NULL; i++)
		printf("%s\n", line_array[i]);
	printf("\n----------\n\n");

	return (line_array);
}
