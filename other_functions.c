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
