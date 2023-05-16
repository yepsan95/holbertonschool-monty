#ifndef MONTY_H
#define MONTY_H

char ***file_array;
extern char ***file_array;

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UNUSED __attribute__((unused))

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void push(stack_t **top, unsigned int line_number);
void pop(stack_t **top, unsigned int line_number);
void pall(stack_t **top, unsigned int line_number);
void pint(stack_t **top, unsigned int line_number);
void swap(stack_t **top, unsigned int line_number);
void add(stack_t **top, unsigned int line_number);
void nop(UNUSED stack_t **top, UNUSED unsigned int line_number);
void search(char *file_buffer, char **line_array, stack_t **top);
void execute(char *opcode, unsigned int n, stack_t **top, int *f);
char *read_file(char *pathname);
char **tokenize(char *file_buffer);
void malloc_failed(void);
void unknown_instruction(unsigned int n, char *opcode);
void free_stack(stack_t **top, UNUSED unsigned int line_number);
void del_whitespace(char *str);
int skip_empty_line(char *file_buffer, unsigned int *j);

#endif /* MONTY_H */
